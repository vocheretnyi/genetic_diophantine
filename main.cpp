#include <iostream>
#include <vector>

#include "Diophantine.h"
#include "Population.h"

using namespace std;

const double mutationRate = 0.01;
const size_t populationSize = 50;

int main() {
    vector<int> coeffs = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int result = 10000;
    Diophantine diophantine(coeffs, result);
    Population population(diophantine, mutationRate, populationSize);

    int iterations = 0;

    while (!population.AnswerReady() && iterations < 50000) {
        ++iterations;
        population.evolve();
        if (iterations % 100 == 0) {
            cout << iterations << "\n";
        }
    }

    cout << "population size = " << populationSize << "\n";
    cout << "mutation rate = " << mutationRate << "\n";
    cout << "iterations = " << iterations << "\n";
    cout << "answer is ready = " << population.AnswerReady() << "\n";

    auto ans = population.GetAnswer();

    for (int x : ans) {
        cout << x << ' ';
    }

    return 0;
}
