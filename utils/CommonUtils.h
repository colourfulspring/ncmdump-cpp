#ifndef NCMDUMP_COMMONUTILS_H
#define NCMDUMP_COMMONUTILS_H

#include <string>
#include <vector>

namespace CommonUtils {

    std::string BytesToHex(const std::string &bytes);

    std::string HexToBytes(const std::string &hex);

    std::vector<uint8_t> StringToUVector(const std::string &str);

    std::string ToLower(const std::string &str);

    std::string ToUpper(const std::string &str);

};// namespace CommonUtils


#endif//NCMDUMP_COMMONUTILS_H
