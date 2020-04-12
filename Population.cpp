//
// Created by vocheretnyi on 10.04.20.
//

#include <ctime>
#include <utility>
#include <algorithm>
#include <cassert>
#include <iostream>
#include "Population.h"

using namespace std;

Population::Population(Diophantine diophantine, double mutationRate, size_t populationSize)
        : diophantine_(move(diophantine)), mutationRate_(mutationRate), answerReady(false) {
    uniform_int_distribution<int> distribution(0, diophantine_.result);

    double invSum = 0.0f;

    population_.resize(populationSize);
    for (DNA& dna : population_) {
        dna.genes.resize(diophantine_.coeffs.size());
        for (int& gen : dna.genes) {
            gen = distribution(random_engine());
        }
        invSum += 1.0 / static_cast<double>(dna.calcFitness(diophantine_));
    }

    for (DNA& dna : population_) {
        dna.likelihood = (1.0 / static_cast<double>(dna.fitness)) / invSum;
    }
}

void Population::evolve() {
    vector<DNA> new_population;
    double invSum = 0.0f;
    uniform_real_distribution<double> real_distribution(0.0, 1.0);

    for (int i = 0; i < population_.size(); ++i) {

        const DNA& dna1 = GetDNAWithProbability(real_distribution(random_engine()));
        const DNA& dna2 = GetDNAWithProbability(real_distribution(random_engine()));
        DNA newDNA = mutation(crossover(dna1, dna2));
        int fitness = newDNA.calcFitness(diophantine_);
        if (fitness == 0) {
            answerReady = true;
            answer = newDNA.genes;
            break;
        }
        invSum += 1.0 / static_cast<double>(fitness);
        new_population.push_back(newDNA);
    }

    population_ = move(new_population);
    for (DNA& dna : population_) {
        dna.likelihood = (1.0 / static_cast<double>(dna.fitness)) / invSum;
    }
}

DNA Population::mutation(DNA dna) const {
    uniform_real_distribution<double> real_distribution(0.0, 1.0);
    uniform_int_distribution<int> int_distribution(0, diophantine_.result);
    for (int& gen : dna.genes) {
        if (real_distribution(random_engine()) < mutationRate_) {
            gen = int_distribution(random_engine());
        }
    }
    return dna;
}

DNA Population::crossover(const DNA& dna1, const DNA& dna2) const {
    uniform_int_distribution<int> int_distribution(0, diophantine_.coeffs.size());
    DNA dna(dna1.genes.size());
    int border = int_distribution(random_engine());
    for (int i = 0; i < dna1.genes.size(); ++i) {
        if (i < border) {
            dna.genes[i] = dna1.genes[i];
        } else {
            dna.genes[i] = dna2.genes[i];
        }
    }
    return dna;
}

const DNA& Population::GetDNAWithProbability(double probability) const {
    double sum = 0.0f;
    for (const DNA& dna : population_) {
        sum += dna.likelihood;
        if (probability < sum) {
            return dna;
        }
    }
    assert(false);
    return DNA();
}

bool Population::AnswerReady() const {
    return answerReady;
}

const vector<int>& Population::GetAnswer() const {
    return answer;
}

std::mt19937& Population::random_engine() {
    static std::random_device random_device;
    static std::mt19937 smt(random_device());
    return smt;
}
