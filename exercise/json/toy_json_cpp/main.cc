//
// Created by ruoshui on 5/29/18.
//



#include <iostream>
#include "toy_json.h"

int main(int argc, char *argv[]) {

    std::cout << sizeof(toy::JsonValue) << std::endl;


    std::string json_string = "{\"name\": \"ruoshui\",\"age\": 30}";
    toy::JsonReader json_reader;
    toy::JsonValue json_value;
    if (json_reader.parser(json_string.c_str())){

    } else {

    }
    return 0;
}