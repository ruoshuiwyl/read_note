//
// Created by ruoshui on 5/29/18.
//



#include <iostream>
#include "toy_json.h"

int main(int argc, char *argv[]) {

//    std::cout << sizeof(toy::JsonValue) << std::endl;


    std::string json_string = "{\"first\" : \"\u3456\", \"name\": \"ruoshui\",\"age\": -30.1E2, \"email\":"
                              " [\"163.com\", \"qq.com\",  {\"for\" : \"gmail.com\"}]}";
    toy::JsonReader json_reader;
    toy::JsonWriter json_writer;
    toy::JsonValue *json_value = json_reader.parser(json_string.c_str());
    if (json_value != nullptr ) {
        std::string json_string;
        if (!json_writer.write(json_value, json_string)){
            std::cout << json_string << std::endl;
        }


    } else {
        std::cerr << "parser Error " << std::endl;

    }
    return 0;
}