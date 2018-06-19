//
// Created by ruoshui on 6/6/18.
//

#include "toy_json.h"
#include "json_value.h"


namespace toy {
    void json_object_destroy(toy::Object *object) {
        for (auto &pair :  *object) {
            json_value_destory(pair.second);
        }
        delete object;
    }

    void json_array_destroy(toy::Array *array) {
        for (int i = 0; i < array->size(); ++i) {
            json_value_destory(array->at(i));
        }
        delete array;
    }

    void json_value_destory(JsonValue *value) {
        switch (value->type) {
            case toy::kObjectType:
                json_object_destroy(reinterpret_cast<toy::Object *>(value->u.value));
                break;
            case toy::kArrayType:
                json_array_destroy(reinterpret_cast<toy::Array *>(value->u.value));
                break;
            case toy::kStringType:
                delete reinterpret_cast<std::string *>(value->u.value);
                break;
            default: // string number true false null
                break;

        }
        delete value;
    }

    void json_destroy(JsonValue *value) {
        if (value->type == toy::kObjectType) {
            json_object_destroy(reinterpret_cast<toy::Object *>(value->u.value));
        }
        delete value;
    }
}