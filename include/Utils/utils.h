#pragma once
#include<vector>
#include <iostream>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& obj) {
    os << "[";
    for (size_t i = 0; i < obj.size() - 1; i++) {
        os << obj[i] << ", ";
    }
    os << obj[obj.size() - 1] << "]";
    return os;
}