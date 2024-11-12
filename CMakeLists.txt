
cmake_minimum_required(VERSION 3.17)
project(multipasstechnicaltest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)