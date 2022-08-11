#include "CommonUtils.h"

#include <cctype>

static char HexDigits[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'b', 'c', 'd', 'e', 'f'};

static int HexToDec(int c) {
    if (std::isdigit(c)) {
        return c - '0';
    } else {
        if (std::isupper(c)) {
            c = std::tolower(c);
        }
        if (c >= 'a' && c <= 'f') {
            return c - 'a' + 10;
        }
    }
    return -1;
}

std::string CommonUtils::BytesToHex(const std::string &bytes) {
    std::string res;

    for (auto it = bytes.begin(); it != bytes.end(); ++it) {
        uint8_t ch = *it;
        int top = (ch >> 4) & 0xF;
        int bot = ch & 0xF;
        res += HexDigits[top];
        res += HexDigits[bot];
    }

    return res;
}
std::string CommonUtils::HexToBytes(const std::string &hex) {
    if (hex.size() % 2 != 0) {
        return std::string();
    }

    std::string res;
    for (size_t i = 0; i < hex.size(); i += 2) {
        int top = HexToDec(hex[i] & 0xFF);
        int bot = HexToDec(hex[i + 1] & 0xFF);
        if (top == -1 || bot == -1) {
            return std::string();
        }
        res += char((top << 4) + bot);
    }
    return res;
}

std::vector<uint8_t> CommonUtils::StringToUVector(const std::string &str) {
    std::vector<uint8_t> res;
    res.reserve(str.size());
    for (auto it = str.begin(); it != str.end(); ++it) {
        res.push_back(*it);
    }
    return res;
}

std::string CommonUtils::ToLower(const std::string &str) {
    std::string res;
    res.reserve(str.size());

    for (char ch : str) {
        if (ch >= 'A' && ch <= 'Z') {
            res += char(ch - ('A' - 'a'));
        } else {
            res += ch;
        }
    }

    return res;
}

std::string CommonUtils::ToUpper(const std::string &str) {
    std::string res;
    res.reserve(str.size());

    for (char ch : str) {
        if (ch >= 'a' && ch <= 'z') {
            res += char(ch - ('a' - 'A'));
        } else {
            res += ch;
        }
    }

    return res;
}
