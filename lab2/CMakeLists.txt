cmake_minimum_required(VERSION 3.20)
project(lab2 LANGUAGES CXX)

add_executable(lab2
        main.cpp
        ../include/Matrix/Matrix.cpp
        ../include/Matrix/defaultmult.cpp
        ../include/Solver/solver.cpp
)

target_include_directories(lab2 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_features(lab2 PRIVATE cxx_std_23)
