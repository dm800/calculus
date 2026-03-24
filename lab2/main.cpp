#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <Matrix/matrix.h>
#include <Solver/solver.h>

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

struct MethodResult {
    std::vector<double> x;
    std::vector<double> y;
};

MethodResult solve_shooting(double a, double b, double A, double B, int n) {
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
    y0[1] = A + h * D0;
    y1[0] = 0;
    y1[1] = D1;

    for (int i = 1; i < n; i++) {
        double h2 = h * h;
        y0[i + 1] = (f(x[i]) * h2 + (2 - q(x[i]) * h2) * y0[i] - (1 - p(x[i]) * h / 2) * y0[i - 1]) /
            (1 + p(x[i]) * h / 2);
        y1[i + 1] = ((2 - q(x[i]) * h2) * y1[i] - (1 - p(x[i]) * h / 2) * y1[i - 1]) /
            (1 + p(x[i]) * h / 2);
    }

    double C = (B - y0[n]) / y1[n];
    for (int i = 1; i < n; i++) {
        y[i] = y0[i] + C * y1[i];
    }

    return {x, y};
}

MethodResult solve_tridiagonal(double a, double b, double A, double B, int n) {
    double h = (b - a) / n;
    double h2 = h * h;

    std::vector<double> x(n + 1);
    std::vector<double> y(n + 1, 0.0);
    for (int i = 0; i < n + 1; i++) {
        x[i] = a + h * i;
    }
    y[0] = A;
    y[n] = B;

    int m = n - 1;
    Matrix system(m, m);
    std::vector<double> rhs(m, 0.0);

    for (int i = 1; i <= n - 1; i++) {
        int row = i - 1;
        double xi = x[i];
        double ai = 1 - p(xi) * h / 2;
        double bi = -(2 - q(xi) * h2);
        double ci = 1 + p(xi) * h / 2;
        double di = f(xi) * h2;

        if (i == 1) {
            di -= ai * A;
        } else {
            system[row][row - 1] = ai;
        }

        system[row][row] = bi;

        if (i == n - 1) {
            di -= ci * B;
        } else {
            system[row][row + 1] = ci;
        }

        rhs[row] = di;
    }

    std::vector<double> inner = solve(system, rhs);
    for (int i = 1; i <= n - 1; i++) {
        y[i] = inner[i - 1];
    }

    return {x, y};
}

// y'' + y' - 2y = 2x + 1
// y(0) = 1; y(1) = 4/3 * e + 2/3 * e^(-2) - 2

int main() {
    double a = 0;
    double b = 1;
    double A = 1;
    double B = 4.0 / 3.0 * std::exp(1) + 2.0 / 3.0 * std::exp(-2) - 2;
    int n = 10;

    MethodResult shooting = solve_shooting(a, b, A, B, n);
    MethodResult tridiagonal = solve_tridiagonal(a, b, A, B, n);

    const int w_x = 10;
    const int w_y = 16;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::left << std::setw(w_x) << "x_i"
              << " | " << std::setw(w_y) << "tridiag_y"
              << " | " << std::setw(w_y) << "shoot_y" << " |\n";

    for (int i = 0; i < n + 1; i++) {
        std::cout << std::left << std::setw(w_x) << shooting.x[i]
                  << " | " << std::setw(w_y) << tridiagonal.y[i]
                  << " | " << std::setw(w_y) << shooting.y[i] << " |\n";
    }

    std::cout << "\n";
    std::cout << std::left << std::setw(w_x) << "x_i"
              << " | " << std::setw(w_y) << "abs_err_trid"
              << " | " << std::setw(w_y) << "abs_err_shoot"
              << " | " << std::setw(w_y) << "true_y" << " |\n";

    for (int i = 0; i < n + 1; i++) {
        double true_y = answer(shooting.x[i]);
        double err_trid = std::abs(tridiagonal.y[i] - true_y);
        double err_shoot = std::abs(shooting.y[i] - true_y);

        std::cout << std::left << std::setw(w_x) << shooting.x[i]
                  << " | " << std::setw(w_y) << err_trid
                  << " | " << std::setw(w_y) << err_shoot
                  << " | " << std::setw(w_y) << true_y << " |\n";
    }
}
