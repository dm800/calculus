cmake_minimum_required(VERSION 3.20)
project(lab3 LANGUAGES CXX)

add_executable(lab3
        main.cpp)

target_compile_features(lab3 PRIVATE cxx_std_23)
