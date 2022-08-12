#include "NCMParser.h"
#include "CommonUtils.h"

#include <fstream>
#include <iostream>
#include <vector>

#include <AES.h>
#include <base64.h>
#include <json/json.h>

using ustring = std::vector<uint8_t>;

static const char coreKeyRaw[] = "687A4852416D736F356B496E62617857";
static const char metaKeyRaw[] = "2331346C6A6B5F215C5D2630553C2728";

static const char ncmHeader[] = "CTENFDAM";

NCMParser::NCMParser() {
}

NCMParser::~NCMParser() {
}

bool NCMParser::Encode() {
    return false;
}

bool NCMParser::Decode() {
    auto core_key = CommonUtils::StringToUVector(CommonUtils::HexToBytes(coreKeyRaw));
    auto meta_key = CommonUtils::StringToUVector(CommonUtils::HexToBytes(metaKeyRaw));

    // Virtual file
    std::stringbuf buf;
    buf.str(data);
    std::istream f(&buf);

    // Check header
    {
        char header[8];
        f.read((char *) header, sizeof(char) * 8);
        if (std::string(header, 8) != ncmHeader) {
            return false;
        }
    }

    ustring key_data;
    {
        f.seekg(2, std::ios::cur);
        uint8_t length_byte[4];
        f.read((char *) length_byte, sizeof(char) * 4);
        uint32_t key_length = length_byte[0];

        auto ans = new uint8_t[key_length];
        f.read((char *) ans, sizeof(char) * key_length);
        for (uint32_t i = 0; i < key_length; ++i)
            ans[i] ^= 0x64u;
        key_data.assign(ans, ans + key_length);
        delete[] ans;
    }

    {
        AES cryptor{AESKeyLength::AES_128};// AES-128 has a key of 16 bytes long, so we use it.
        auto t{cryptor.DecryptECB(key_data, core_key)};
        t.resize(t.size() - t.back());
        key_data.assign(t.begin() + 17, t.end());
    }
    auto key_length = key_data.size();

    ustring key_box(256, 0);
    for (unsigned int i = 1; i < 256u; ++i)
        key_box[i] = i;

    uint8_t last_byte = 0, key_offset = 0;
    for (int i = 0; i < 256; ++i) {
        uint8_t swap = key_box[i];
        uint8_t c = swap + last_byte + key_data[key_offset];
        ++key_offset;
        if (key_offset >= key_length)
            key_offset = 0;
        key_box[i] = key_box[c];
        key_box[c] = swap;
        last_byte = c;
    }

    ustring meta_data;
    {
        uint32_t meta_length;
        f.read((char *) &meta_length, sizeof(char) * 4);
        auto ans = new uint8_t[meta_length];
        f.read((char *) ans, sizeof(char) * meta_length);
        for (int i = 0; i < meta_length; ++i) {
            ans[i] ^= 0x63u;
        }
        meta_data.assign(ans + 22, ans + meta_length);
        std::string temp(meta_data.begin(), meta_data.end());
        temp = base64_decode(temp);
        meta_data.assign(temp.begin(), temp.end());

        delete[] ans;
    }

    std::string music_format;
    {
        AES cryptor{AESKeyLength::AES_128};
        auto t{cryptor.DecryptECB(meta_data, meta_key)};
        t.resize(t.size() - t.back());
        std::string meta_data_string(t.begin() + 6, t.end());

        Json::Value meta_data_json;
        Json::Reader reader;
        if (!reader.parse(meta_data_string, meta_data_json)) {
            return false;
        }
        music_format = meta_data_json["format"].asString();
    }

    {
        uint32_t crc32;
        f.read((char *) &crc32, sizeof(uint32_t));
        uint32_t image_size;
        f.seekg(5, std::ios::cur);
        f.read((char *) &image_size, sizeof(uint32_t));

        // auto image_data = new uint8_t[image_size];
        // f.read((char *) image_data, sizeof(uint8_t) * image_size); // ?
        // delete[] image_data;
        f.seekg(image_size, std::ios::cur);
    }

    std::string output;
    {
        auto chunk = new uint8_t[0x8000];
        while (true) {
            f.read((char *) chunk, 0x8000);
            auto chunk_length = f.gcount();
            if (!chunk_length) {
                break;
            }
            for (unsigned int i = 1; i <= chunk_length; ++i) {
                auto j = i & 0xffu;
                chunk[i - 1] ^= key_box[(key_box[j] + key_box[(key_box[j] + j) & 0xffu]) & 0xffu];
            }
            output += std::string((char *) chunk, chunk_length);
        }
        delete[] chunk;
    }

    data = std::move(output);
    format = music_format;

    return true;
}

void NCMParser::Clear() {
    data.clear();
    format.clear();
}
