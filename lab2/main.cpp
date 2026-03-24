#include <iostream>
#include <vector>
#include <Matrix/matrix.h>
#include <cmath>
#include <Solver/solver.h>
#include <Utils/utils.h> // принт векторов

double p(double x) {
    return 1;
}

double q(double x) {
    return -2;
}

double f(double x) {
    return 2 * x + 1;
}

double answer(double x) {
    return 4.0 / 3.0 * std::exp(x) + 2.0 / 3.0 * std::exp(-2 * x) - x - 1;
}

struct ShootingResult {
    std::vector<double> x;
    std::vector<double> y0;
    std::vector<double> y1;
    std::vector<double> y;
};

ShootingResult solve_shooting(double a, double b, double A, double B, size_t n) {
    double h = (b - a) / n;
    double D0 = 0;
    double D1 = h;

    std::vector<double> x(n + 1);
    std::vector<double> y0(n + 1);
    std::vector<double> y1(n + 1);
    std::vector<double> y(n + 1);

    for (size_t i = 0; i < n + 1; i++) {
        x[i] = a + h * static_cast<double>(i);
    }

    y[0] = A;
    y[n] = B;
    y0[0] = A;
    y0[1] = D0;
    y1[0] = 0;
    y1[1] = D1;

    for (size_t i = 1; i < n; i++) {
        double h2 = std::pow(h, 2);
        y0[i + 1] = (f(x[i]) * h2 + (2 - q(x[i]) * h2) * y0[i] - (1 - p(x[i]) * h / 2) * y0[i - 1]) /
            (1 + (p(x[i]) * h / 2));
        y1[i + 1] = ((2 - q(x[i]) * h2) * y1[i] - (1 - p(x[i]) * h / 2) * y1[i - 1]) /
            (1 + (p(x[i]) * h / 2));
    }

    double C = (B - y0[n]) / y1[n];
    for (size_t i = 1; i < n; i++) {
        y[i] = y0[i] + C * y1[i];
    }

    return {x, y0, y1, y};
}

// y'' + y' - 2y = 2x + 1
// y(0) = 1; y(1) = 4/3 * e + 2/3 * e^(-2) - 2

int main() {
    double a = 0;
    double b = 1;
    double A = answer(a);
    double B = answer(b);
    size_t n = 10;
    ShootingResult result = solve_shooting(a, b, A, B, n);
    std::cout << '\n';
    for (size_t i = 0; i < result.x.size(); i++) {
        std::cout << result.y[i] << " " << answer(result.x[i]) << std::endl;
    }
}
