#include <iostream>
#include <vector>
#include <Matrix/matrix.h>
#include <cmath>
#include <Solver/solver.h>
#include <Utils/utils.h> // принт векторов

double p(double x) {
    return 5;
}

double q(double x) {
    return -3;
}

double f(double x) {
    return 3 * std::exp(x);
}

// y'' + 5y' - 3y = 3 * e^x
// y(0) = 1; y(1) = e ~ 2,718281828

int main() {
    double a = 0;
    double b = 1;
    double A = 1;
    double B = 2.71828;
    size_t n = 10;
    double h = (b - a) / n;
    double D0 = 0;
    double D1 = h;



    std::vector<double> x(n + 1);
    std::vector<double> y0(n + 1);
    std::vector<double> y1(n + 1);
    std::vector<double> y(n + 1);
    for (int i = 0; i < n + 1; i++) {
        x[i] = a + h * i;
    }
    y[0] = A;
    y[n] = B;
    y0[0] = A;
    y0[1] = D0;
    y1[0] = 0;
    y1[1] = D1;
    for (int i = 1; i < n; i++) {
        double h2 = std::pow(h, 2);
        y0[i + 1] = (f(x[i]) * h2 + (2 - q(x[i]) * h2) * y0[i] - (1 - p(x[i]) * h / 2) * y0[i - 1]) /
            (1 + (p(x[i]) * h / 2));
        y1[i + 1] = ((2 - q(x[i]) * h2) * y1[i] - (1 - p(x[i]) * h / 2) * y1[i - 1]) /
            (1 + (p(x[i]) * h / 2));
    }
    double C = (B - y0[n]) / y1[n];
    std::cout << '\n';
    for (int i = 1; i < n; i++) {
        y[i] = y0[i] + C * y1[i];
    }
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    std::cout << y0 << std::endl;
    std::cout << y1 << std::endl;
}