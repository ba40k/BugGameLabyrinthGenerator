//
// Created by radamir on 01.02.25.
//

#include "Population.h"
#include <functional>
std::shared_ptr<spdlog::logger> Population::logger = spdlog::rotating_logger_mt("PopulationLogger", "../../logs/PopulationLog.txt", max_size, max_files);
void Population::refreshPopulationSize() {
    populationSize = population.size();
}

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
    refreshPopulationSize();
}
void Population::shrinkPopulation() {
    while(population.size() > maxPopulationSize) {
        population.erase(population.begin());
    }
}
Labyrinth Population::getBestLabyrinth() const {
    auto labyrinth = population.rbegin();
    return *labyrinth;
}
Population::Population(int _populationSize) {
    populationSize = _populationSize;
    while (_populationSize--) {
        Labyrinth newLabyrinth;
        population.insert(newLabyrinth);
    }
    maxPopulationSize = std::max(maxPopulationSize, populationSize*10);
}
void Population::setMaxPopulationSize(int _populationSize) {
    maxPopulationSize = _populationSize;
    shrinkPopulation();
    refreshPopulationSize();
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
    refreshPopulationSize();
}
