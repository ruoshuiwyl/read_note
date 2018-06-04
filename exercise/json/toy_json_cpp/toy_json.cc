//
// Created by ruoshui on 5/29/18.
//



#include <cstring>
#include <cmath>
#include <cctype>
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
            JsonValue *value = new JsonValue(kObjectType);
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
            case 'n': // parser null
                value = parserBool(json_str, end_ptr);
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
                        break;
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
        JsonValue *value;
        if (*json_str == 't') {
            if (json_str[1] == 'r' && json_str[2] == 'u' && json_str[3] == 'e'){
                value = new JsonValue(kTureType, true);
            }
            *end_ptr = (char *) json_str + 4;
        } else if (*json_str == 'f') {
            if (json_str[1] == 'a' && json_str[2] == 'l' && json_str[3] == 's' && json_str[4] == 'e'){
                value = new JsonValue(kTureType, false);
            }
            *end_ptr = (char *) json_str + 5;
        } else if (*json_str == 'n') {
            if (json_str[1] == 'u' && json_str[2] == 'l' && json_str[3] == 'l'){
                value = new JsonValue(kNullType);
            }
            *end_ptr = (char *) json_str + 4;
        }
        return value;

    }
    JsonValue* JsonReader::parserArray(const char *json_str, char **end_ptr) {
        JsonValue *value = new JsonValue(kArrayType);
        const  char *ptr = json_str ;
        char *end;
        if (*ptr == '[') {
            ptr++;
        }
        while (*ptr != ']') {
            ptr = skipspaces(ptr);
            JsonValue *value = parserValue(ptr, &end);
            value->u.array.push_back(value);
            ptr = skipspaces(end);
            if (*ptr == ','){
                ptr++;
            }
        }
        if (*ptr == ']') {
            ptr = skipspaces(++ptr);
        }
        *end_ptr = (char *)ptr;
        return value;
    }

    JsonValue* JsonReader::parserNumber(const char *json_str, char **end_ptr) {
        const char *ptr = json_str;
        char *end;
        JsonValue *value = new JsonValue(kIntergeType);
        long val = parserInteger(ptr, &end);
        value->u.l = val;
        if (*end == '.') {
            value->type = kDoubleType;
            double d = parserFrac(ptr, &end);
            d = d + val;
            if (*end == 'e' || *end == 'E') {
                end++;
                if (*end == '-') {
                    long l = parserInteger(ptr, &end);
                    d = d * pow(10, l);
                } else if (isdigit(*end)){
                    long l = parserInteger(ptr, &end);
                    d = d * pow(10, l);
                } else if (*end == '+'){
                    long l = parserInteger(ptr, &end);
                    d = d * pow(10, l);
                }
            }
            value->u.d = d;
        } else if (*end == 'e' || *end == 'E') {
            double d = val;
            end++;
            if (*end == '-') {
                long l = parserInteger(ptr, &end);
                d = d * pow(10, l);
            } else if (isdigit(*end)){
                long l = parserInteger(ptr, &end);
                d = d * pow(10, l);
            } else if (*end == '+'){
                long l = parserInteger(ptr, &end);
                d = d * pow(10, l);
            }
            value->u.d = d;
        }
    }

    double JsonReader::parserFrac(const char *json_str, char **end_ptr) {
        double value = 0.0;
        double ten_num  = 10.0;
        while(*json_str >= '0' && *json_str <= '9') {
            value += (*json_str++ - '0') / (ten_num);
            ten_num *= 10.0;
        }
        *end_ptr = (char*)json_str;
        return  value;
    }

    long JsonReader::parserInteger(const char *json_str, char **end_ptr) {
        long val = 0;
        while (isdigit(*json_str)){
            val += val * 10 + (*json_str - '0');
            json_str++;
        }
        *end_ptr = (char *)json_str;
        return val;
    }
}