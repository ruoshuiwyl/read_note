//
// Created by ruoshui on 5/29/18.
//

#ifndef PROJECT_TOY_JSON_H
#define PROJECT_TOY_JSON_H


#include <cstddef>
#include <string>

namespace toy{

//    enum JsonType{
//        kNullType,
//        kTureType,
//        kFalseType,
//        kObjectType,
//        kArrayType,
//        kStringType,
//        kNumberType,
//    };

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
    struct JsonString{
        int length;
        char *str;
    };

    struct JsonObject{
        JsonString key;
        JsonValue *value;
    };

    struct JsonArray {
        int array_len;
        JsonValue *value;
    };

    struct JsonValue{
        struct JsonValue *parent;
        JsonType type;
        union {
            int i;
            long l;
            double d;
            JsonString str;
            JsonObject object;
            JsonArray array;
        } u;

    };




    class JsonReader{
    public:
        int parse(const char *json_str, JsonValue &value);
        int parse(const char *json_str, const int json_len, JsonValue &value);

    private:
        int parseObject(const char *json_str, );

    };
    class JsonWriter{
    public :
        std::string write(const JsonValue &value);


    };


}

#endif //PROJECT_TOY_JSON_H
