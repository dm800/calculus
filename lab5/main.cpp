#include <Utils/utils.h>

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

    double delta1 = std::abs(z_xa - y_a);
    double delta2 = std::abs(z_xg - y_g);
    double delta3 = std::abs(z_xa - y_g);
    double delta4 = std::abs(z_xg - y_a);
    double delta5 = std::abs(z_xh - y_a);
    double delta6 = std::abs(z_xa - y_h);
    double delta7 = std::abs(z_xh - y_h);
    double delta8 = std::abs(z_xh - y_g);
    double delta9 = std::abs(z_xg - y_h);

    std::cout << delta1 << " " << delta2 << " " << delta3 << " " << delta4 << " "
    << delta5 << " " << delta6 << " " << delta7 << " " << delta8 << " " << delta9 << " " << std::endl;

    // наименьшая дельта - delta3 => тип функции y = a * e^(bx)
    // после линеаризации получаем y' = a'x + b, где
    // y' = ln(y), a' = b, b' = ln(a)


    return 0;
}