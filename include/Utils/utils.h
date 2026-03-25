#pragma once
#include <vector>
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

inline size_t utf8_len(const std::string& s) {
    size_t len = 0;
    for (unsigned char c : s) {
        if ((c & 0xC0) != 0x80) {
            ++len;
        }
    }
    return len;
}

inline void print_padded_utf8(const std::string& s, size_t width) {
    std::cout << s;
    size_t visible = utf8_len(s);
    if (visible < width) {
        std::cout << std::string(width - visible, ' ');
    }
}