//
// Created by ruoshui on 6/3/18.
//

#include "encodings.h"


namespace toy{



    std::string utf8_encoding::encode(const char *json_str) {
        std::string result;
        unsigned char uc_b1, uc_b2, uc_b3, uc_b4;
        if ((uc_b1 = HexValue (*++json_str)) == 0xFF ||
        (uc_b2 = HexValue (*++json_str)) == 0xFF ||
        (uc_b3 = HexValue (*++json_str)) == 0xFF ||
        (uc_b4 = HexValue (*++json_str)) == 0xFF) {
            return result;
        }
        uc_b1 = (uc_b1 << 4) | uc_b2;
        uc_b2 = (uc_b3 << 4) | uc_b4;
        uint32_t uchar = (uc_b1 << 8) | uc_b2;
        if (uchar <= 0x7ff) {
            char c1 = 0xC0 | (uchar>>6);
            char c2 = 0x80 | (uchar&0x3f);
            result.push_back(c1);
            result.push_back(c2);
        } else if (uchar <= 0x07ff) {
            char c1 = 0xE0 | (uchar >> 12);
            char c2 = 0x80 | ((uchar >> 6) & 0x3f);
            char c3 = 0x80 | (uchar & 0x3f);
            result.push_back(c1);
            result.push_back(c2);
            result.push_back(c3);
        } else if (uchar <= 0xffff) {
            char c1 = 0xF0 | (uchar >> 18);
            char c2 = 0x80 | ((uchar >> 12) & 0x3f);
            char c3 = 0x80 | ((uchar >> 6) & 0x3f);
            char c4 = 0x80 | (uchar & 0x3f);
            result.push_back(c1);
            result.push_back(c2);
            result.push_back(c3);
            result.push_back(c4);
        }
        return result;
    }

    int utf8_encoding::decode(const char *value_str, std::string &json_str) {
        int utf8_size;
        int utf8[4];
        int value;
        if (*value_str > 0xF0) {
            utf8_size = 4;
            value = value_str[0] & 0x7;
            value <<= 6;
            value |= value_str[1] & 0x3f;
            value <<= 6;
            value |= value_str[2] & 0x3f;
            value <<= 6;
            value |= value_str[3] & 0x3f;
        } else if (*value_str > 0xE0) {
            utf8_size = 3;
            value = value_str[0] & 0xf;
            value <<= 6;
            value |= value_str[1] & 0x3f;
            value <<= 6;
            value |= value_str[2] & 0x3f;
        } else if (*value_str > 0xC0) {
            utf8_size = 2;
            value = value_str[0] & 0x1f;
            value <<= 6;
            value |= value_str[1] & 0x3f;
        } else {
            value = value_str[0];
            utf8_size = 1;
            json_str.push_back(*value_str);
        }
        utf8[0] = (value >> 12)& 0xf;
        utf8[1] = (value >> 8)& 0xf;
        utf8[2] = (value >> 4)& 0xf;
        utf8[3] = value & 0xf;
        json_str.append("\\u");
        json_str.push_back(HexChar(utf8[0]));
        json_str.push_back(HexChar(utf8[1]));
        json_str.push_back(HexChar(utf8[2]));
        json_str.push_back(HexChar(utf8[3]));
        return utf8_size;
    }


    char utf8_encoding::HexValue(char c) {
            if (isdigit(c))
                return c - '0';

            switch (c) {
                case 'a': case 'A': return 0x0A;
                case 'b': case 'B': return 0x0B;
                case 'c': case 'C': return 0x0C;
                case 'd': case 'D': return 0x0D;
                case 'e': case 'E': return 0x0E;
                case 'f': case 'F': return 0x0F;
                default: return 0xFF;
            }

    }

    static std::string kHexTable = "0123456789abcdef";

    char utf8_encoding::HexChar(char c) {
      return kHexTable[c];
    }
}