//
// Created by radamir on 01.02.25.
//

#ifndef POPULATION_H
#define POPULATION_H
#include <set>
#include "Generator.h"
#include "Labyrinth.h"
#include <functional>
template<typename PopulationMember>
class Population {
public:
    explicit Population(int _populationSize = initialPopulationSize);
    PopulationMember getBestLabyrinth() const; // дает лучший лабиринт
    void refreshGeneration(); // создает новые лабиринты и удаляет худшие
    void mutate();// вызывает мутации у членов популяции
    void setMaxPopulationSize(int _populationSize); // установить максимальный размер популяции
    int getPopulationSize(); // возвращает размер популяции
    std::multiset<PopulationMember>::iterator getRandomLabyrinth(); // получить случайный член популяции
    ~Population() = default;
private:
    static const int max_size = 1048576 * 5;
    static const int max_files = 3;
    static std::shared_ptr<spdlog::logger> logger;
    void refreshPopulationSize();
    void shrinkPopulation();
    int maxPopulationSize = 2000;
    static const int initialPopulationSize = 50;
    std::multiset<PopulationMember> population;
    int populationSize;
};
template<class PopulationMember>
std::shared_ptr<spdlog::logger> Population<PopulationMember>::logger = spdlog::rotating_logger_mt("PopulationLogger", "../../logs/PopulationLog.txt", max_size, max_files);
template<class PopulationMember>
void Population<PopulationMember>::refreshPopulationSize() {
    logger->info("Entrypoint| Population::refreshPopulationSize");
    populationSize = population.size();
    logger->info("End| Population::refreshPopulationSize");
}
template<class PopulationMember>
int Population<PopulationMember>::getPopulationSize() {
    logger->info("Entrypoint| Population::getPopulationSize");
    logger->info("End| Population::getPopulationSize");
    return populationSize;
}
template<class PopulationMember>
std::multiset<PopulationMember>::iterator Population<PopulationMember>::getRandomLabyrinth() {
        logger->info("Entrypoint| Population::getRandomLabyrinth");
        auto it = population.begin();
        Generator generator;
        int index = generator.getRandomInt(0, populationSize - 1);
        std::advance(it, index);
        logger->info("End| Population::getRandomLabyrinth");
        return it;
}
template<class PopulationMember>
void Population<PopulationMember>::mutate() {
    logger->info("Entrypoint| Population::mutate");
    Generator generator;
    int iterations = generator.getRandomInt(1,populationSize);
    while (iterations--) {
        std::multiset<Labyrinth>::iterator labyrinth = getRandomLabyrinth();
        auto newLabyrinth = *labyrinth;
        newLabyrinth.mutation();
        //population.erase(labyrinth);
        population.insert(newLabyrinth);
    }
    logger->info("End| Population::mutate");
    shrinkPopulation();
    refreshPopulationSize();
}
template<class PopulationMember>
void Population<PopulationMember>::shrinkPopulation() {
    logger->info("Entrypoint| Population::shrinkPopulation");
    while(population.size() > maxPopulationSize) {
        population.erase(population.begin());
    }
    logger->info("End| Population::shrinkPopulation");
}
template<class PopulationMember>
PopulationMember Population<PopulationMember>::getBestLabyrinth() const {
    logger->info("Entrypoint| Population::getBestLabyrinth");
    auto labyrinth = population.rbegin();
    logger->info("End| Population::getBestLabyrinth");
    return *labyrinth;
}
template<class PopulationMember>
Population<PopulationMember>::Population(int _populationSize) {
    logger->info("Entrypoint| Population::Population");
    populationSize = _populationSize;
    while (_populationSize--) {
        Labyrinth newLabyrinth;
        population.insert(newLabyrinth);
    }
    maxPopulationSize = std::max(maxPopulationSize, populationSize*10);
    logger->info("End| Population::Population");
}
template<class PopulationMember>
void Population<PopulationMember>::setMaxPopulationSize(int _populationSize) {
    logger->info("Entrypoint| Population::setMaxPopulationSize");
    maxPopulationSize = _populationSize;
    shrinkPopulation();
    refreshPopulationSize();
    logger->info("End| Population::setMaxPopulationSize");
}
template<class PopulationMember>
void Population<PopulationMember>::refreshGeneration() {
    logger->info("Entrypoint| Population::refreshGeneration");
    Generator generator;
    int iterations = generator.getRandomInt(1, population.size());
    while (iterations--) {
        auto father = getRandomLabyrinth();
        auto mother = getRandomLabyrinth();
        auto child = father->getDescendant((*mother));
        population.insert(child);
    }
    shrinkPopulation();
    refreshPopulationSize();
    logger->info("End| Population::refreshGeneration");
}



#endif //POPULATION_H
