cmake_minimum_required(VERSION 3.20)
project(lab6 LANGUAGES CXX)

add_executable(lab6
        main.cpp)

target_include_directories(lab6 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_features(lab6 PRIVATE cxx_std_23)
