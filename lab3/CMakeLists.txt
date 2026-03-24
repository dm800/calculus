cmake_minimum_required(VERSION 3.20)
project(lab3 LANGUAGES CXX)

add_executable(lab3
        main.cpp)

target_include_directories(lab3 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_features(lab3 PRIVATE cxx_std_23)
