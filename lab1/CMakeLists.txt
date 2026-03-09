cmake_minimum_required(VERSION 3.20)
project(lab1 LANGUAGES CXX)

add_executable(lab1
        main.cpp
        ../include/Matrix/Matrix.cpp
        ../include/Matrix/defaultmult.cpp
        ../include/Solver/solver.cpp
        ../include/Solver/solver.h
)

target_include_directories(lab1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_features(lab1 PRIVATE cxx_std_23)
