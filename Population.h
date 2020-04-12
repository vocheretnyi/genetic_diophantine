//
// Created by vocheretnyi on 10.04.20.
//

#pragma once

#include <vector>
#include <random>

#include "Diophantine.h"
#include "DNA.h"

class Population {
public:
    Population(Diophantine diophantine, double mutationRate, size_t populationSize);

    void evolve();

    bool AnswerReady() const;

    const std::vector<int>& GetAnswer() const;

private:
    DNA mutation(DNA dna) const;

    DNA crossover(const DNA& dna1, const DNA& dna2) const;

    const DNA& GetDNAWithProbability(double probability) const;

    static std::mt19937& random_engine();

    Diophantine diophantine_;
    std::vector<DNA> population_;
    double mutationRate_;

    bool answerReady;
    std::vector<int> answer;
};

