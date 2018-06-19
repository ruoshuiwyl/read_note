

set(CMAKE_CXX_COMPILER /usr/bin/g++-7)
add_definitions(-std=c++17)
add_executable(toy_json toy_json.h toy_json.cc example.cc encodings.cc encodings.h json_value.cc json_value.hpp)
target_link_libraries(toy_json )