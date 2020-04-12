//
// Created by vocheretnyi on 10.04.20.
//

#pragma once

#include <vector>

#include "Diophantine.h"

struct DNA {
    std::vector<int> genes;
    int fitness;
    double likelihood;

    DNA(size_t len) : DNA() {
        genes.resize(len);
    }

    DNA() {
        fitness = 0;
        likelihood = 0.0;
    }

    bool operator==(const DNA& other) {
        return genes == other.genes;
    }

    int calcFitness(const Diophantine& diophantine) {
        int sum = 0;
        for (int i = 0; i < genes.size(); ++i) {
            sum += genes[i] * diophantine.coeffs[i];
        }
        fitness = abs(sum - diophantine.result);
        return fitness;
    }
};

