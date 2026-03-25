#include <Utils/utils.h>

double f1_x(double x, double y) {
    return -1;
}

double f1_y(double x, double y) {
    return std::cos(y + 2);
}

double f2_x(double x, double y) {
    return - std::sin(x - 2);
}

double f2_y(double x, double y) {
    return 1;
}

double f1(double x, double y) {
    return std::sin(y + 2) - x - 1.5;
}

double f2(double x, double y) {
    return y + std::cos(x - 2) - 0.5;
}



// sin(y + 2) - x = 1.5
// y + cos(x - 2) = 0.5
int main() {
    double x = -1.5;
    double y = 1.5;

    const double eps = 1e-6;
    const int max_iter = 100;

    for (int k = 0; k < max_iter; k++) {
        double a11 = f1_x(x, y);
        double a12 = f1_y(x, y);
        double a21 = f2_x(x, y);
        double a22 = f2_y(x, y);

        double b1 = -f1(x, y);
        double b2 = -f2(x, y);

        // Крамер
        double det = a11 * a22 - a12 * a21;

        double dx = (b1 * a22 - b2 * a12) / det;
        double dy = (a11 * b2 - a21 * b1) / det;

        x += dx;
        y += dy;

        if (std::sqrt(dx*dx + dy*dy) < eps) {
            break;
        }
    }

    std::cout << "x = " << x << "\n";
    std::cout << "y = " << y << "\n";

    return 0;
}