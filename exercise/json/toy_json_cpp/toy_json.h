//
// Created by ruoshui on 5/29/18.
//

#ifndef PROJECT_TOY_JSON_H
#define PROJECT_TOY_JSON_H


#include <cstddef>
#include <string>
#include <unordered_map>
#include <string>
#include <vector>
#include <variant>
#include "encodings.h"
#include "json_value.h"

namespace toy{

    class JsonReader{
    public:
        JsonValue * parser(const char *json_str);
        JsonValue * parser(const char *json_str, const size_t json_len);

    private:
        std::string parserKey(const char *json_str, char **end_ptr);
        JsonValue * parserValue(const char *json_str, char **end_ptr);
        JsonValue * parserObject(const char *json_str, char **end_ptr);
        JsonValue * parserArray(const char *json_str,  char **end_ptr);
        std::string  parserString(const char *json_str,  char **end_ptr);
        JsonValue * parserStringValue(const char *json_str, char **end_ptr);
        JsonValue * parserNumber(const char *json_str,  char **end_ptr);
        double parserFrac(const char *json_str, char **end_ptr);
        long parserInteger(const char *json_str,  char **end_ptr);
        JsonValue * parserBool(const char *json_str, char **end_ptr);
        const char *skipspaces(const char *json_str);

        utf8_encoding utf8_encoding_;

    };


    class JsonWriter{
    public :
        int write(const JsonValue *value, std::string &json_str);
    private:
        int writeObject(const JsonValue *object, std::string &json_str, int depth);
        int writeString(const JsonValue *value, std::string &json_str);
        int writeString(const std::string &val, std::string &json_str);
        int writeArray(const JsonValue *value, std::string &json_str, int depth);
        int writeValue(const JsonValue *value, std::string &json_str, int depth);
        utf8_encoding utf8_encoding_;

    };


}

#endif //PROJECT_TOY_JSON_H
