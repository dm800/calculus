#include <iostream>
#include <Matrix/matrix.h>
#include <cmath>

#include <Solver/solver.h>
#include <Utils/utils.h>

int main() {
    std::vector<std::vector<double>> data = {
        {4, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 4, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 4, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 4, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 4, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 4, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 4, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 4, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 4},
    };

    int n = 10;
    double a = 0;
    double b = 1;
    std::vector<double> x_i = std::vector<double>(n + 1);
    std::vector<double> y_i = std::vector<double>(n + 1);
    for (int i = 0; i <= n; i++) {
        x_i[i] = a + i * ((b - a) / n);
        y_i[i] = std::exp(x_i[i]);
    }

    double h = (b - a) / n;
    std::vector<double> cs = std::vector<double>(n - 1);
    for (int i = 1; i < n; i++) {
        cs[i - 1] = 3 * (y_i[i + 1] - 2 * y_i[i] + y_i[i - 1]) / std::pow(h, 2);
    }
    Matrix test(data);
    std::vector<double> c_i = solve(test, cs);
    c_i.push_back(0);
    c_i.insert(c_i.begin(), 0);
    std::vector<double> a_i = std::vector<double>(n);
    std::vector<double> b_i = std::vector<double>(n);
    std::vector<double> d_i = std::vector<double>(n);
    for (int i = 0; i < n; i++) {
        a_i[i] = y_i[i];
    }
    for (int i = 0; i < n - 1; i++) {
        d_i[i] = (c_i[i + 1] - c_i[i]) / (3 * h);
    }
    d_i[n - 1] = - c_i[n] / 3 * h;
    for (int i = 0; i < n - 1; i++) {
        b_i[i] = (y_i[i + 1] - y_i[i]) / h - (h / 3) * (c_i[i + 1] + 2 * c_i[i]);
    }
    b_i[n - 1] = (y_i[n] - y_i[n - 1]) / h - 2 * h / 3 * c_i[n - 1];

    std::cout << "a_i: " << a_i;
    std::cout << "\nb_i: " << b_i;
    std::cout << "\nc_i: " << c_i;
    std::cout << "\nd_i: " << d_i;
    std::cout << "\nd_i\tx_i\tf(x_i)\t\ts_i(x_i)\t%\t in nodes \n";
    for (int i = 0; i < n; i++) {
        double s_i = a_i[i] +
            b_i[i] * (x_i[i] - x_i[i]) +
            c_i[i] * std::pow(x_i[i] - x_i[i], 2) +
            d_i[i] * std::pow(x_i[i] - x_i[i], 3);
        double delta_i = std::abs(s_i - y_i[i]);
        std::cout << delta_i << "\t" << x_i[i] << "\t" << y_i[i] << "\t\t" << s_i << "\t\t" << delta_i / y_i[i] << "\n";
    }
    std::vector<double> new_x = std::vector<double>();
    for (auto elem : x_i) {
        new_x.push_back(elem + h / 2);
    }
    std::vector<double> new_y = std::vector<double>();
    for (auto elem : new_x) {
        new_y.push_back(std::exp(elem));
    }
    std::cout << "\nd_i\t\t\tx_i\t\tf(x_i)\t\ts_i(x_i)\t%\t\t in middles\n";
    for (int i = 0; i < n; i++) {
        double s_i = a_i[i] +
            b_i[i] * (new_x[i] - x_i[i]) +
            c_i[i] * std::pow(new_x[i] - x_i[i], 2) +
            d_i[i] * std::pow(new_x[i] - x_i[i], 3);
        double delta_i = std::abs(s_i - new_y[i]);
        std::cout << delta_i << "\t" << new_x[i] << "\t" << new_y[i] << "\t\t" << s_i << "\t\t" << delta_i / y_i[i] <<  "\n";
    }
    std::cout << std::endl;
    return 0;
}
