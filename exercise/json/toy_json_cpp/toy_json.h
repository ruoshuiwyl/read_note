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

namespace toy{


    enum JsonType {
        kNullType,
        kTureType,
        kFalseType,
        kObjectType,
        kArrayType,
        kStringType,
        kIntergeType,
        kDoubleType,
    };

    struct JsonValue;
    struct JsonObject{
        std::unordered_map<std::string, JsonValue *> objects;
    };

    struct JsonArray {
        std::vector<JsonValue * > array;
    };

    struct JsonValue {
//        struct JsonValue *parent;
        JsonType type;
        union {
            bool b;
            int i;
            long l;
            double d;
            std::string *str;
            JsonObject object;
            JsonArray array;
        } u;
    };
//
//    enum JsonFlag {
//        kObjectStart = '{',
//        kObjectEnd = '}',
//        kArrarStart = '[',
//        kArrayEnd = ']',
//        kStringStart = '\"',
//        kStringEnd = '\"',
//        kDelimiter = ':',
//    };







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
        JsonValue * parserInteger(const char *json_str,  char **end_ptr);
        JsonValue * parserBool(const char *json_str,  char **end_ptr);
        JsonValue * parserNull(const char *json_str, char **end_ptr);
        const char *skipspaces(const char *json_str);
        JsonType parserJsonType(const char *json_str);

    };


    class JsonWriter{
    public :
        std::string write(const  JsonValue &value);


    };


}

#endif //PROJECT_TOY_JSON_H
