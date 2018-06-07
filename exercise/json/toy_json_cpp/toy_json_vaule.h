//
// Created by ruoshui on 6/7/18.
//

#ifndef PROJECT_TOY_JSON_VAULE_H
#define PROJECT_TOY_JSON_VAULE_H

#include <cstdint>
#include <string>
#include <vector>
#include <bits/unordered_map.h>

namespace  toy {

    enum class value_t : std::uint8_t {
        null,
        object,
        array,
        string,
        boolean,
        number_integer,
        number_double,
    };



    class BasicJson {
        BasicJson ();

        using double_t = double;


        union json_value {
            std::unordered_map<std::string, BasicJson> *object;
            std::vector<BasicJson>  *array;
            std::string *str;
            bool     boolean;
            long      l_value;
            double   d_value;
            json_value() = default;
            json_value(const std::string &value) {
                str = new std::string(value);
            }
            json_value(const
            json_value(value_t t) {
                switch (t) {
                    case value_t::object:
                        object = new std::unordered_map<std::string, BasicJson>;
                        break;
                    case value_t::array:
                        array = new std::vector<BasicJson>;
                        break;
                    case value_t::string:
                        str = new std::string;
                        break;
                    case value_t::boolean:
                        boolean = false;
                        break;
                    case value_t::number_integer:
                        l_value = 0;
                        break;
                    case value_t::number_double:
                        d_value = 0;
                        break;
                    case value_t::null:
                        object = nullptr;
                        break;
                    default:
                        break;
                }
            }
        };


    private:
        value_t type_;
        json_value value_;


    };


}

#endif //PROJECT_TOY_JSON_VAULE_H
