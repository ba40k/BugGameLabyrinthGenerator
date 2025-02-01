//
// Created by radamir on 01.02.25.
//

#include "Population.h"
#include <functional>
std::shared_ptr<spdlog::logger> Population::logger = spdlog::rotating_logger_mt("PopulationLogger", "../../logs/PopulationLog.txt", max_size, max_files);
void Population::refreshPopulationSize() {
    logger->info("Entrypoint| Population::refreshPopulationSize");
    populationSize = population.size();
    logger->info("End| Population::refreshPopulationSize");
}
int Population::getPopulationSize() {
    logger->info("Entrypoint| Population::getPopulationSize");
    logger->info("End| Population::getPopulationSize");
    return populationSize;
}

std::set<Labyrinth>::iterator Population::getRandomLabyrinth() {
        logger->info("Entrypoint| Population::getRandomLabyrinth");
        auto it = population.begin();
        Generator generator;
        int index = generator.getRandomInt(0, populationSize - 1);
        std::advance(it, index);
        logger->info("End| Population::getRandomLabyrinth");
        return it;
}
void Population::mutate() {
    logger->info("Entrypoint| Population::mutate");
    Generator generator;
    int iterations = generator.getRandomInt(1,populationSize);
    while (iterations--) {
        std::set<Labyrinth>::iterator labyrinth = getRandomLabyrinth();
        auto newLabyrinth = *labyrinth;
        newLabyrinth.mutation();
        population.erase(labyrinth);
        population.insert(newLabyrinth);
    }
    logger->info("End| Population::mutate");
    refreshPopulationSize();
}
void Population::shrinkPopulation() {
    logger->info("Entrypoint| Population::shrinkPopulation");
    while(population.size() > maxPopulationSize) {
        population.erase(population.begin());
    }
    logger->info("End| Population::shrinkPopulation");
}
Labyrinth Population::getBestLabyrinth() const {
    logger->info("Entrypoint| Population::getBestLabyrinth");
    auto labyrinth = population.rbegin();
    logger->info("End| Population::getBestLabyrinth");
    return *labyrinth;
}
Population::Population(int _populationSize) {
    logger->info("Entrypoint| Population::Population");
    populationSize = _populationSize;
    while (_populationSize--) {
        Labyrinth newLabyrinth;
        population.insert(newLabyrinth);
    }
    maxPopulationSize = std::max(maxPopulationSize, populationSize*10);
    logger->info("End| Population::Population");
}
void Population::setMaxPopulationSize(int _populationSize) {
    logger->info("Entrypoint| Population::setMaxPopulationSize");
    maxPopulationSize = _populationSize;
    shrinkPopulation();
    refreshPopulationSize();
    logger->info("End| Population::setMaxPopulationSize");
}
void Population::refreshGeneration() {
    logger->info("Entrypoint| Population::refreshGeneration");
    Generator generator;
    int iterations = generator.getRandomInt(1, population.size());
    while (iterations--) {
        auto father = getRandomLabyrinth();
        auto mother = getRandomLabyrinth();
        auto child = father->getDescendant((*mother));
        population.insert(child);
    }
    refreshPopulationSize();
    logger->info("End| Population::refreshGeneration");
}
