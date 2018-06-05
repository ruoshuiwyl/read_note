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

namespace toy{


    enum JsonType {
        kNullType,
        kTrueType,
        kFalseType,
        kObjectType,
        kArrayType,
        kStringType,
        kIntegerType,
        kDoubleType,
    };

    struct JsonValue;
    typedef std::unordered_map<std::string, JsonValue *> Object;
    typedef std::vector<JsonValue *> Array;


    struct JsonValue {

        JsonValue(JsonType t) {
            type = t;
            u.i = 0;
        } // null
        JsonValue(bool value) {
            u.b = value;
            if (value){
                type = kTrueType;
            } else {
                type = kFalseType;

            }
        }// true or false
        JsonValue(int value){
            type = kIntegerType;
            u.i = value;
        }// Number
        JsonValue(double value){
            type = kDoubleType;
            u.d = value;
        }// Number
        JsonValue(std::string &value) {
            type = kStringType;
            u.value = new std::string(value);
        }
         //

        //        struct JsonValue *parent;
        JsonType type;
        union {
            bool b;
            int i;
            long l;
            double d;
            void *value;
//            void *str;
//            void *object;
//            void *array;
//            std::unordered_map<std::string, JsonValue *> object;
//            std::vector<JsonValue*> array;
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
        JsonValue * parserNumber(const char *json_str,  char **end_ptr);
        double parserFrac(const char *json_str, char **end_ptr);
        long parserInteger(const char *json_str,  char **end_ptr);
        JsonValue * parserBool(const char *json_str, char **end_ptr);
        const char *skipspaces(const char *json_str);

        utf8_encoding utf8_encoding_;

    };


    class JsonWriter{
    public :
        std::string write(const  JsonValue *value);

    private:
        int writeObject(const toy::JsonValue *object, std::string &json_str, int depth);
        int writeString(const std::string &str, std::string &json_str);
        int writeArray(const JsonValue *value, std::string &json_str, int depth);
        int writeValue(const toy::JsonValue *value, std::string &json_str, int depth);
        utf8_encoding utf8_encoding_;

    };


}

#endif //PROJECT_TOY_JSON_H
