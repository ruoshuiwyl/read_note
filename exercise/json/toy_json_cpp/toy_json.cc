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
                    case '\"' : value.push_back('\"'); ptr++; break;
                    case '\\' : value.push_back('\\'); ptr++; break;
                    case '/' : value.push_back('/') ;  ptr++; break;
                    case 'b' : value.push_back('\b');  ptr++; break;
                    case 'f' : value.push_back('\f');  ptr++; break;
                    case 'n' : value.push_back('\n');  ptr++; break;
                    case 'r' : value.push_back('\r');  ptr++; break;
                    case 't' : value.push_back('\t');  ptr++; break;
                    case 'u' : value.append(utf8_encoding_.encode(ptr));
                        ptr += 4;
                        break;
                }
            }
        }
        if (*ptr == '"') {
            ptr++;
        }
        *end_ptr = (char *)ptr;
        return value;
    }

    JsonValue* JsonReader::parserStringValue(const char *json_str, char **end_ptr) {
        std::string str = parserString(json_str, end_ptr);
        JsonValue *value = new JsonValue(str);
        return value;
    }

    JsonValue* JsonReader::parserBool(const char *json_str, char **end_ptr) {
        JsonValue *value;
        if (*json_str == 't') {
            if (json_str[1] == 'r' && json_str[2] == 'u' && json_str[3] == 'e'){
                value = new JsonValue(true);
            }
            *end_ptr = (char *) json_str + 4;
        } else if (*json_str == 'f') {
            if (json_str[1] == 'a' && json_str[2] == 'l' && json_str[3] == 's' && json_str[4] == 'e'){
                value = new JsonValue(false);
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
            reinterpret_cast<Array *>(value->u.value)->push_back(value);
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
        JsonValue *value = new JsonValue(kIntegerType);
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
            value->type = kDoubleType;
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
        *end_ptr = end;
        return value;
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
        bool neg_flag = false;
        if (*json_str == '-') {
            neg_flag = true;
            json_str++;
        }
        while (isdigit(*json_str)){
            val += val * 10 + (*json_str - '0');
            json_str++;
        }
        *end_ptr = (char *)json_str;
        return neg_flag? val * -1 : val;
    }










    std::string JsonWriter::write(const toy::JsonValue *value) {
        std::string json_str;
        if (value->type == kObjectType) {
            if (writeObject(value, json_str, 0);
        }
        return json_str;
    }


    int JsonWriter::writeObject(const toy::JsonValue *object, std::string &json_str, int depth) {
        int result;
        if (object->u.object.empty()) {
            json_str.append("{}\n");
        } else {
            json_str.append("{\n");
            int object_idx = 0;
            for (auto &pair : object->u.object) {
                for (int i = 0; i < depth; ++i){
                    json_str.append("\t");
                }
                writeString(pair.first, json_str);
                json_str.append(": ");
                if (!writeValue(pair.second, json_str, depth)){
                    if (object_idx != object->u.object.size() - 1) {
                        json_str.append(",\n");
                    } else {
                        json_str.append("\n");
                    }
                } else {
                    result = 2;
                }

            }
        }
        return result;
    }

    int JsonWriter::writeString(const std::string &str, std::string &json_str) {
        json_str.append("\"");
        for (int i = 0; i < str.size(); ){
            if (str[i] < 0x80) {
                switch (str[i]) {
                    case '\\':
                        json_str.append("\\");
                        break;
                    case '\t':
                        json_str.append("\\t");
                        break;
                    case '\"':
                        json_str.append("\\\"");
                        break;
                    case '/':
                        json_str.append("\\/");
                        break;
                    case '\b':
                        json_str.append("\\b");
                        break;
                    case '\f':
                        json_str.append("\\f");
                        break;
                    case '\n':
                        json_str.append("\\n");
                        break;
                    case '\r':
                        json_str.append("\\n");
                        break;
                    default:
                        json_str.push_back(str[i]);
                        break;

                }
                i++;
            } else {
                const char * ptr = str.c_str() + i;
                i += utf8_encoding.decode(ptr, json_str);
            }
        }
        json_str.append("\"");
        return 0;
    }


    int JsonWriter::writeArray(const JsonValue *value, std::string &json_str, int depth) {
        int result = 0;
        json_str.append("[\n");
        for (int i = 0; i < value->u.array.size(); ++i){
            for (int i= 0; i <= depth; ++i) {
                json_str.append("\t");
            }
            if (!writeValue(value->u.array[i], json_str, depth)) {
                if (i !=  value->u.array.size() - 1) {
                    json_str.append(",\n");
                } else {
                    json_str.append("\n");
                }
            } else {
                result = 1;
            }
        }
        for (int i= 0; i < depth; ++i) {
            json_str.append("\t");
        }
        json_str.append("[\n");
        return result;

    }

    int JsonWriter::writeValue(const toy::JsonValue *value, std::string &json_str, int depth) {
        int result;
        switch (value->type) {
            case kNullType:
                json_str.append("null");
                break;
            case kTrueType:
                json_str.append("true");
                break;
            case kFalseType:
                json_str.append("false");
                break;
            case kObjectType:
                result = writeObject(value, json_str, depth + 1);
                break;
            case kArrayType:
                result = writeArray(value, json_str, depth + 1);
                break;
            case kStringType:
                result = writeString(value->u.str, json_str);
                break;
            case kIntegerType:
                json_str += std::to_string(value->u.l);
                break;
            case kDoubleType:
                json_str += std::to_string(value->u.d);
                break;
        }
    }


}