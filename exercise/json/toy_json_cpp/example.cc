//
// Created by ruoshui on 5/29/18.
//



#include <iostream>
#include "toy_json.h"


void test_case_one() {
    std::string json_string = "{\"first\" : \"\u4f60\u597d\", \"name\": \"ruoshui\",\"age\": -30.1E2, \"email\":"
                              " [\"163.com\", \"qq.com\",  {\"for\" : \"gmail.com\"}]}";
    toy::JsonReader json_reader;
    toy::JsonWriter json_writer;
    toy::JsonValue *json_value = json_reader.parser(json_string.c_str());
    if (json_value != nullptr ) {
        std::string json_string;
        if (!json_writer.write(json_value, json_string)){
            std::cout << json_string << std::endl;
            json_destroy(json_value);
        }


    } else {
        std::cerr << "parser Error " << std::endl;

    }
}

void test_case2() {
    toy::JsonValue json_value;
    json_value["name"] = "ruoshui";
    json_value["age"] = 29;
}
int main(int argc, char *argv[]) {

//    std::cout << sizeof(toy::JsonValue) << std::endl;
    test_case2();


    return 0;
}