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
    const int maxNumberOfMutations = 20;
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
    logger->info("Entrypoint| Population::mutate\n");
   // std::cout<<"Entrypoint| Population::mutate\n";
    Generator generator;
    int numberOfMutations = generator.getRandomInt(1,maxNumberOfMutations);
    for (int i =0;i<numberOfMutations;i++) {
        auto randomLabyrinth = getRandomLabyrinth();
        auto newLabyrinth = *randomLabyrinth;
        newLabyrinth.mutation();
        population.insert(newLabyrinth);
    }
    logger->info("End| Population::mutate\n");
}
template<class PopulationMember>
void Population<PopulationMember>::shrinkPopulation() {
    logger->info("Entrypoint| Population::shrinkPopulation\n");
    while(population.size() > maxPopulationSize) {
        population.erase(population.begin());
    }
    logger->info("End| Population::shrinkPopulation\n");
}
template<class PopulationMember>
PopulationMember Population<PopulationMember>::getBestLabyrinth() const {
    logger->info("Entrypoint| Population::getBestLabyrinth\n");
  //  std::cout<<"Entrypoint| Population::getBestLabyrinth\n";
    auto labyrinth = population.rbegin();
    logger->info("End| Population::getBestLabyrinth");
    return *labyrinth;
}
template<class PopulationMember>
Population<PopulationMember>::Population(int _populationSize) {
    logger->info("Entrypoint| Population::Population");
    populationSize = _populationSize;
    while (population.size() != _populationSize) {
        Labyrinth newLabyrinth;
        population.insert(newLabyrinth);
    }
    maxPopulationSize = std::max(maxPopulationSize, populationSize*2);
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
    logger->info("Entrypoint| Population::refreshGeneration\n");
   // std::cout<<"Entrypoint| Population::refreshGeneration\n";
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



#endif //POPULATION_H
