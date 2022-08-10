#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "cryptlib.h"
#include "rijndael.h"
#include "osrng.h"
#include "hex.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "binascii.h"

#ifdef __cplusplus
};
#endif

typedef std::basic_string<uint8_t> ustring;

ustring a2b_hex(const char *hex_key) {
    int key_len = strlen(hex_key);
    auto key = new uint8_t[key_len / 2 + 1];

    auto res = binascii_unhexlify(hex_key, key_len, key);
    if (res) {
        std::cerr << "Error! Invalid hex key!" << std::endl;
        exit(-1);
    }
    ustring ans{key};

    delete[] key;
    return ans;
}

std::string b2a_hex(const unsigned char *key, const int key_len) {
    auto hex_key = new char[key_len * 2 + 1];

    int res = binascii_hexlify(key, key_len, hex_key);
    if (res) {
        std::cerr << "Error! Invalid key!" << std::endl;
        exit(-1);
    }
    std::string ans{hex_key};

    delete[] hex_key;
    return ans;
}

void dump(const std::string &file_path) {
    auto core_key{a2b_hex("687A4852416D736F356B496E62617857")};
    auto meta_key{a2b_hex("2331346C6A6B5F215C5D2630553C2728")};
    auto unpad = [](ustring &str) {
        if (typeid(str.back()).name() == "int") {
        }
    };

    std::ifstream f{file_path, std::ios::binary | std::ios::in};
    if (!f) {
        std::cerr << "Error! Open file failed!" << std::endl;
        exit(-1);
    }

    {
        auto header = new char[8];
        f.read((char *) header, sizeof(char) * 8);
        assert(b2a_hex(reinterpret_cast<const unsigned char *>(header), 8) == "4354454e4644414d");
        delete[] header;
    }

    uint32_t key_length;
    {
        f.seekg(2, std::ios::cur);
        uint8_t length_byte[4];
        f.read((char *) length_byte, sizeof(char) * 4);
        key_length = length_byte[0];
    }

    ustring key_data;
    {
        auto ans = new uint8_t[key_length];
        f.read((char *) ans, sizeof(char) * key_length);
        for (uint32_t i = 0; i < key_length; ++i)
            ans[i] ^= 0x64u;
        key_data = ans;
        delete [] ans;
    }

    {

    }
}

int main() {
    dump("D:\\tmp\\netease_music_cpp\\data\\1.ncm");
    std::cout << "Dump Successfully!" << std::endl;
    return 0;
}
