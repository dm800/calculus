#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <Utils/utils.h>

#define EPSILON 0.001

double func(double x) {
    return (x + 2) * std::exp(x - 1);
}

double calc_pr(double func(double), double a, double b, size_t n) {
    double h = (b - a) / n;
    double x = a;
    double s = 0;
    for (size_t i = 0; i < n; i++) {
        s += h * func(x + h / 2);
        x += h;
    }
    return s;
}

double calc_tr(double func(double), double a, double b, size_t n) {
    double h = (b - a) / n;
    double x = a + h;
    double s = (func(a) + func(b)) / 2;
    for (size_t i = 1; i < n; i++) {
        s += func(x);
        x += h;
    }
    return s * h;
}

double calc_Sm(double func(double), double a, double b, size_t n) {
    double s = 0;
    double h = (b - a) / n;
    double x = a + h;
    for (size_t i = 1; i < n; i += 2) {
        s += func(x) * 4;
        x += h * 2;
    }
    x = a + 2 * h;
    for (size_t i = 2; i < n; i += 2) {
        s += func(x) * 2;
        x += h * 2;
    }
    s += func(a);
    s += func(b);
    return s * h / 3;
}

struct answer {
    std::string name;
    size_t n;
    double I;
    double R;
    double IR;
};

int main() {
    double a = -2;
    double b = 1;
    size_t n = 2;

    double eps1 = 100;
    double eps2 = 100;
    double eps3 = 100;
    bool end1 = false;
    bool end2 = false;
    bool end3 = false;
    size_t count = 3;
    size_t step = 0;
    std::vector<answer> answers = {};
    while (count != 0) {
        if (std::abs(eps1) < EPSILON && !end1) {
            count--;
            double I = calc_pr(func, a, b, n);
            answer pr = {
                "Метод прямоугольников",
                n, I, eps1, I + eps1
            };
            answers.push_back(pr);
            end1 = true;
        } else if (std::abs(eps1) > EPSILON) {
            eps1 = (calc_pr(func, a, b, n * 2) - calc_pr(func, a, b, n)) / (std::pow(2, 2) - 1);
        }
        if (std::abs(eps2) < EPSILON && !end2) {
            count--;
            double I = calc_tr(func, a, b, n);
            answer tr = {
                "Метод трапеций",
                n, I, eps2, I + eps2
            };
            answers.push_back(tr);
            end2 = true;
        } else if (std::abs(eps2) > EPSILON) {
            eps2 = (calc_tr(func, a, b, n * 2) - calc_tr(func, a, b, n)) / (std::pow(2, 2) - 1);
        }
        if (std::abs(eps3) < EPSILON && !end3) {
            count--;
            double I = calc_Sm(func, a, b, n);
            answer Sm = {
                "Метод Симпсона",
                n, I, eps3, I + eps3
            };
            answers.push_back(Sm);
            end3 = true;
        } else if (std::abs(eps3) > EPSILON) {
            eps3 = (calc_Sm(func, a, b, n * 2) - calc_Sm(func, a, b, n)) / (std::pow(2, 4) - 1);
        }
        n *= 2;
        step += 1;
    }
    size_t name_width = utf8_len("Название метода");
    for (const auto& elem : answers) {
        name_width = std::max(name_width, utf8_len(elem.name));
    }

    print_padded_utf8 ("Название метода", name_width);
    std::cout << " | " << std::left << std::setw(6) << "n" << " | " << std::setw(12) << "I*" << " | "
              << std::setw(12) << "R" << " | " << std::setw(12) << "I* + R" << " |\n";
    for (const auto& elem : answers) {
        print_padded_utf8(elem.name, name_width);
        std::cout << " | " << std::left << std::setw(6) << elem.n << " | " << std::setw(12) << elem.I << " | "
                  << std::setw(12) << elem.R << " | " << std::setw(12) << elem.IR << " |\n";
    }
}
