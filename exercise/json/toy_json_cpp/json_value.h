//
// Created by ruoshui on 6/6/18.
//

#ifndef PROJECT_JSON_VALUE_H
#define PROJECT_JSON_VALUE_H

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>
#include <variant>

namespace toy {
    struct JsonValue;

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

    typedef std::unordered_map<std::string, JsonValue *> Object;
    typedef std::vector<JsonValue *> Array;

    struct JsonValue {
        JsonValue(){
            type= kObjectType;
            u.value = nullptr;
        }

        JsonValue(JsonType t) {
            type = t;
            u.value = 0;
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
        //        struct JsonValue *parent;
        JsonType type;
        union {
            bool b;
            int i;
            long l;
            double d;
            void *value;
        } u;
    };

    void json_object_destroy(std::unordered_map<std::string, JsonValue *> *object);

    void json_array_destroy(std::vector<JsonValue *> *array);

    void json_value_destory(JsonValue *value);

    void json_destroy(JsonValue *value);
}


#endif //PROJECT_JSON_VALUE_H
