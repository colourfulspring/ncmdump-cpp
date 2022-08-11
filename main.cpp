#include "utils/CommonUtils.h"
#include "utils/NCMParser.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ncmdump [ncm file] [-o [output path]]" << std::endl;
        return 0;
    }

    std::string in_path;
    std::string out_path;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            out_path = argv[i + 1];
            i++;
            continue;
        }
        in_path = argv[i];
    }

    if (in_path.size() < 4 || CommonUtils::ToLower(in_path.substr(in_path.size() - 4)) != ".ncm") {
        std::cout << "Input file suffix should be \"ncm\"." << std::endl;
        return -1;
    }
    if (out_path.empty()) {
        out_path = in_path.substr(0, in_path.size() - 4);
    } else {
        auto idx = out_path.find_last_of('.');
        if (idx != std::string::npos) {
            out_path = out_path.substr(0, idx);
        }
    }

    std::fstream f;
    f.open(in_path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "Read file failed." << std::endl;
        return -1;
    }

    NCMParser parser;
    parser.data = std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
    f.close();

    if (!parser.Decode()) {
        std::cout << "Decode file failed." << std::endl;
        return -1;
    }
    out_path += "." + parser.format;

    f.open(out_path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "Write file failed." << std::endl;
        return -1;
    }
    f.write(parser.data.data(), parser.data.size());
    f.close();

    std::cout << "Decode to " << parser.format << " file finished." << std::endl;

    return 0;
}
