//
// Created by ruoshui on 5/29/18.
//



#include <cstring>
#include "toy_json.h"


namespace toy {
    JsonValue * JsonReader::parser(const char *json_str) {
        return parser(json_str, strlen(json_str));
    }

     JsonValue * JsonReader::parser(const char *json_str, const size_t json_len) {
        const char *ptr = skipspaces(json_str);
        char *end_ptr;
        JsonValue *json_value =  parserObject(ptr, &end_ptr);
        if (end_ptr - json_str != json_len) {
            return nullptr;
        }
        return  json_value;
    }


    JsonValue* JsonReader::parserObject(const char *json_str, char **end_ptr) {

        if (*json_str == '{') {
            JsonValue *value = new JsonValue;
            value->type = kObjectType;
            const char *ptr = json_str;
            char *end_ptr = nullptr;
            if (*ptr == '"') {
                std::string key = parserKey(ptr, &end_ptr);
                ptr = skipspaces(end_ptr);
                if (*ptr == ':' ) {
                    ptr = skipspaces(ptr);

                } else {

                }
            } else if (*ptr == '}') {
                return value;
            }
        } else {
            return nullptr;
        }
    }

    const char* JsonReader::skipspaces(const char *json_str) {
        const char *ptr = json_str;
        while (isspace(*ptr)) {
            ptr++;
        }
        return ptr;
    }

    std::string JsonReader::parserKey(const char *json_str, char **end_ptr) {
        return  parserString(json_str, end_ptr);
    }

    JsonValue* JsonReader::parserValue(const char *json_str, char **end_ptr) {
        const char *ptr = skipspaces(json_str);
        JsonValue *value;
        switch  (*ptr) {
            case '{': //parser Object
                value = parserObject(ptr, end_ptr);
                break;
            case '[': // parser Array
                value = parserArray(ptr, end_ptr);
                break;
            case '"' : // parser String
                value = parserStringValue(json_str, end_ptr);
                break;
            case 't': // parser true
            case 'f': // parser false
                value = parserBool(json_str, end_ptr);
                break;
            case 'n': // parser null
                break;
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': // parser number
                value = parserNumber(json_str, end_ptr);
                break;
            default:
                break;


        }
        return value;
    }

    std::string JsonReader::parserString(const char *json_str, char **end_ptr) {
        std::string value;
        const char *ptr = json_str;
        while (*ptr != '"') {
            if (*ptr == '\\') {
                ptr++;
                switch (*ptr) {
                    case '\"' : value.push_back('\"'); break;
                    case '\\' : value.push_back('\\'); break;
                    case '/' : value.push_back('/') ; break;
                    case 'b' : value.push_back('\b'); break;
                    case 'f' : value.push_back('\f'); break;
                    case 'n' : value.push_back('\n'); break;
                    case 'r' : value.push_back('\r'); break;
                    case 't' : value.push_back('\t'); break;
                    case 'u' :
                }
            }
        }
        return value;
    }

    JsonValue* JsonReader::parserStringValue(const char *json_str, char **end_ptr) {
        JsonValue *value = new JsonValue(kStringType, parserString(json_str, end_ptr));
        return value;
    }

    JsonValue* JsonReader::parserBool(const char *json_str, char **end_ptr) {

    }
    JsonValue* JsonReader::parserArray(const char *json_str, char **end_ptr) {

    }

}