#include "solver.h"

#include <cassert>
#include <iostream>

std::vector<double> solve(Matrix data, const std::vector<double> &ds) {
    size_t rows = data.rows;
    size_t collumns = data.collumns;
    assert(rows == collumns);
    assert(rows == ds.size());
    std::vector<double> answer(collumns, 0);
    std::vector<double> alphas(collumns, 0);
    std::vector<double> betas(collumns, 0);
    // alpha + beta calcs:
    assert(data[0][0] != 0);

    alphas[0] = -data[0][1] / data[0][0];
    betas[0] = ds[0] / data[0][0];
    for (int i = 1; i < collumns; i++) {
        if (i != collumns - 1) {
            //std::cout << data[i][i + 1] << " " << alphas[i - 1] << " " << data[i][i - 1] << "\n";
            alphas[i] = -(data[i][i + 1] / (alphas[i - 1] * data[i][i - 1] + data[i][i]));
        }
        betas[i] = (ds[i] - data[i][i - 1] * betas[i - 1]) / (data[i][i - 1] * alphas[i - 1] + data[i][i]);
    }
    /*for (int i = 0; i < 4; i++) {
        std::cout << alphas[i] << " " << betas[i] << std::endl;
    }*/

    answer[collumns - 1] = betas[collumns - 1];

    for (int i = collumns - 2; i >= 0; i--) {
        answer[i] = alphas[i] * answer[i + 1] + betas[i];
    }

    return answer;
}
