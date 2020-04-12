#pragma once

#include <vector>

struct Diophantine {
    std::vector<int> coeffs;
    int result;

    Diophantine(std::vector<int> coeffs_, int result_) :
            coeffs(std::move(coeffs_)), result(result_) {}
};

