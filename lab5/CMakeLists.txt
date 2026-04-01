cmake_minimum_required(VERSION 3.20)
project(lab5 LANGUAGES CXX)

add_executable(lab5
        main.cpp)

target_include_directories(lab5 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_features(lab5 PRIVATE cxx_std_23)
