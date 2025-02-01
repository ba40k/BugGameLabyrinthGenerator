//
// Created by radamir on 01.02.25.
//

#include "Population.h"
#include <functional>
std::set<Labyrinth>::iterator Population::getRandomLabyrinth() {
        auto it = population.begin();
        Generator generator;
        int index = generator.getRandomInt(0, populationSize - 1);
        std::advance(it, index);
        return it;
}

void Population::mutate() {
    Generator generator;
    int iterations = generator.getRandomInt(1,populationSize);
    while (iterations--) {
        std::set<Labyrinth>::iterator labyrinth = getRandomLabyrinth();
        auto newLabyrinth = *labyrinth;
        newLabyrinth.mutation();
        population.erase(labyrinth);
        population.insert(newLabyrinth);
    }
}
void Population::shrinkPopulation() {
    while(population.size() > maxPopulationSize) {
        population.erase(population.begin());
    }
}

void Population::refreshGeneration() {
    Generator generator;
    int iterations = generator.getRandomInt(1, population.size());
    while (iterations--) {
        auto father = getRandomLabyrinth();
        auto mother = getRandomLabyrinth();
        auto child = father->getDescendant((*mother));
        population.insert(child);
    }
}
