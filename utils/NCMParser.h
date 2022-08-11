#ifndef NCM_DUMP_NCMPARSER_H
#define NCM_DUMP_NCMPARSER_H

#include <string>

class NCMParser {
public:
    NCMParser();
    ~NCMParser();

    bool Encode();
    bool Decode();

    void Clear();

    std::string data;
    std::string format;
};


#endif//NCM_DUMP_NCMPARSER_H
