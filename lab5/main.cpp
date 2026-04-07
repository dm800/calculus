#include <Utils/utils.h>
#include <cmath>

int main() {

    // получены на листочке
    double x_a = 3;
    double x_g = 2.24;
    double x_h = 1.67;

    double y_a = 1.23;
    double y_g = 0.74;
    double y_h = 0.45;

    double z_xa = 0.74;
    double z_xg = 1.19;
    double z_xh = 1.68;

    std::vector<double> x = {1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};
    std::vector<double> y = {2.20, 2.02, 1.40, 1.30, 0.45, 0.46, 0.33, 0.41, 0.25};

    double delta1 = std::abs(z_xa - y_a);
    double delta2 = std::abs(z_xg - y_g);
    double delta3 = std::abs(z_xa - y_g);
    double delta4 = std::abs(z_xg - y_a);
    double delta5 = std::abs(z_xh - y_a);
    double delta6 = std::abs(z_xa - y_h);
    double delta7 = std::abs(z_xh - y_h);
    double delta8 = std::abs(z_xh - y_g);
    double delta9 = std::abs(z_xg - y_h);

    std::cout << "deltas: ";
    std::cout << delta1 << " " << delta2 << " " << delta3 << " " << delta4 << " "
    << delta5 << " " << delta6 << " " << delta7 << " " << delta8 << " " << delta9 << " " << std::endl;

    // наименьшая дельта - delta3 => тип функции y = a * e^(bx)
    // после линеаризации получаем y' = a'x + b, где
    // y' = ln(y), a' = b, b' = ln(a)

    double sum_x = 0.0;
    double sum_y_lin = 0.0;
    double sum_x2 = 0.0;
    double sum_xy = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        double y_lin = std::log(y[i]);
        sum_x += x[i];
        sum_y_lin += y_lin;
        sum_x2 += x[i] * x[i];
        sum_xy += x[i] * y_lin;
    }

    size_t n = x.size();
    double denominator = n * sum_x2 - sum_x * sum_x;


    double a_prime = (n * sum_xy - sum_x * sum_y_lin) / denominator;
    double b_prime = (sum_y_lin - a_prime * sum_x) / n;


    double b = a_prime;
    double a = std::exp(b_prime);

    std::cout << "Before linear: a' = " << a_prime << ", b' = " << b_prime << std::endl;
    std::cout << "After linear: a = " << a << ", b = " << b << std::endl;
    std::cout << std::fixed;
    std::cout.precision(6);
    std::cout << " x_i      | y_i       | f(x_i)" << std::endl;
    double deltas = 0;
    for (int i = 0; i < n; i++) {
        double y1 = a * std::exp(b * x[i]);
        std::cout.width(9);
        std::cout << x[i] << " | ";
        std::cout.width(9);
        std::cout << y[i] << " | ";
        std::cout << y1 << std::endl;
        double dd = (y[i] - y1) * (y[i] - y1);
        deltas += dd;
    }
    std::cout << "sum of |f(x) - y_i|^2 = " << deltas << std::endl;
    return 0;
}
