#include <iostream>
#include <cmath>
#include <iomanip>

double f(double x1, double x2) {
    return x1*x1 + x2*x2 + pow(x1,4)*pow(x2,4) + 0.1*x1 + 0.2*x2;
}

double f_x(double x1, double x2) {
    return 2*x1 + 4*pow(x1,3)*pow(x2,4) + 0.1;
}

double f_y(double x1, double x2) {
    return 2*x2 + 4*pow(x2,3)*pow(x1,4) + 0.2;
}

double f_xx(double x1, double x2) {
    return 2 + 12*x1*x1*pow(x2,4);
}

double f_yy(double x1, double x2) {
    return 2 + 12*x2*x2*pow(x1,4);
}

double f_xy(double x1, double x2) {
    return 16*pow(x1,3)*pow(x2,3);
}

int main() {

    double x1 = 0.0;
    double x2 = 0.0;

    const double eps = 0.001;
    const int max_iter = 100;

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "k | "
              << std::setw(10) << "x1"
              << std::setw(10) << "x2"
              << " | "
              << std::setw(10) << "f(x)"
              << " | "
              << std::setw(10) << "norm\n";

    std::cout << "----------------------------------------------------------\n";

    for (int k = 0; k < max_iter; ++k) {

        double gx = f_x(x1, x2);
        double gy = f_y(x1, x2);

        double norm = std::sqrt(gx*gx + gy*gy);

        std::cout << std::setw(2) << k << " | "
                  << std::setw(10) << x1
                  << std::setw(10) << x2 << " | "
                  << std::setw(10) << f(x1, x2) << " | "
                  << std::setw(10) << norm << "\n";

        if (norm < eps) break;

        double fxx = f_xx(x1, x2);
        double fyy = f_yy(x1, x2);
        double fxy = f_xy(x1, x2);

        double numerator = gx*gx + gy*gy;
        double denominator = fxx*gx*gx + 2*fxy*gx*gy + fyy*gy*gy;

        if (std::abs(denominator) < 1e-12) break;

        double t = numerator / denominator;

        x1 -= t * gx;
        x2 -= t * gy;
    }

    std::cout << "Result: x1 = " << x1 << ", x2 = " << x2 << "\n";
    std::cout << "f(x) = " << f(x1, x2) << "\n";

    return 0;
}