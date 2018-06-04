//
// Created by ruoshui on 6/3/18.
//

#ifndef PROJECT_ENCODINGS_H
#define PROJECT_ENCODINGS_H


#include <string>

namespace toy {

    class utf8_encoding {

    public:
         std::string encode(const char *json_str);
         int decode(const char *value_str, std::string &json_str);

    private:
        char HexValue(char c);
        char HexChar(char c);

    };
}


#endif //PROJECT_ENCODINGS_H
