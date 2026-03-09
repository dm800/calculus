#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>

#define EPSILON 0.001

double func(double x) {
    return std::exp(x);
}

double calc_pr(double func(double), double a, double b, size_t n) {
    double h = (b - a) / n;
    double x = a;
    double s = 0;
    for (int i = 0; i < n; i++) {
        s += h * func(x + h / 2);
        x += h;
    }
    return s;
}

double calc_tr(double func(double), double a, double b, size_t n) {
    double h = (b - a) / n;
    double x = a;
    double s = (func(a) + func(b)) / 2;
    for (int i = 0; i < n; i++) {
        s += h * func(x);
        x += h;
    }
    return s;
}

struct answer {
    std::string name;
    size_t n;
    double I;
    double R;
    double IR;
};

size_t utf8_len(const std::string& s) {
    size_t len = 0;
    for (unsigned char c : s) {
        if ((c & 0xC0) != 0x80) {
            ++len;
        }
    }
    return len;
}

void print_padded_utf8(const std::string& s, size_t width) {
    std::cout << s;
    size_t visible = utf8_len(s);
    if (visible < width) {
        std::cout << std::string(width - visible, ' ');
    }
}

int main() {
    double a = 0;
    double b = 1;
    size_t n = 2;

    double eps1 = 100;
    double eps2 = 100;
    bool end1 = false;
    bool end2 = false;
    size_t count = 2;
    size_t step = 0;
    std::vector<answer> answers = {};
    while (count != 0) {
        if (eps1 < EPSILON && !end1) {
            count--;
            double I = calc_pr(func, a, b, n);
            answer pr = {
                "Метод прямоугольников",
                n, I, eps1, I + eps1
            };
            answers.push_back(pr);
            end1 = true;
        } else if (eps1 > EPSILON) {
            eps1 = std::abs((calc_pr(func, a, b, n) - calc_pr(func, a, b, n * 2)) / (std::pow(2, 2) - 1));
        }
        if (eps2 < EPSILON && !end2) {
            count--;
            double I = calc_tr(func, a, b, n);
            answer tr = {
                "Метод трапеций",
                n, I, eps1, I + eps1
            };
            answers.push_back(tr);
            end2 = true;
        } else if (eps2 > EPSILON) {
            eps2 = std::abs((calc_tr(func, a, b, n / 2) - calc_tr(func, a, b, n)) / (std::pow(2, 2) - 1));
        }
        n *= 2;
        step += 1;
    }
    size_t name_width = utf8_len("Название метода");
    for (const auto& elem : answers) {
        name_width = std::max(name_width, utf8_len(elem.name));
    }

    print_padded_utf8("Название метода", name_width);
    std::cout << " | " << std::left << std::setw(6) << "n" << " | " << std::setw(12) << "I*" << " | "
              << std::setw(12) << "R" << " | " << std::setw(12) << "I* + R" << " |\n";
    for (const auto& elem : answers) {
        print_padded_utf8(elem.name, name_width);
        std::cout << " | " << std::left << std::setw(6) << elem.n << " | " << std::setw(12) << elem.I << " | "
                  << std::setw(12) << elem.R << " | " << std::setw(12) << elem.IR << " |\n";
    }
}
