cmake_minimum_required(VERSION 3.10)

project(cmake)

add_executable(cmake book.cpp)

set_target_properties(
    cmake PROPERTIES
    CXX_STANDART 11
    CXX_STANDART_REQUIRED ON
)