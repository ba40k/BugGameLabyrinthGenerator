//
// Created by radamir on 01.02.25.
//

#ifndef POPULATION_H
#define POPULATION_H
#include <set>
#include "Generator.h"
#include "Labyrinth.h"

class Population {
public:
    Population(int _populationSize = initialPopulationSize);
    Labyrinth getBestLabyrinth() const; // дает лучший лабиринт
    void refreshGeneration(); // создает новые лабиринты и удаляет худшие
    void mutate();// вызывает мутации у членов популяции
    void setMaxPopulationSize(int _populationSize);
    std::set<Labyrinth>::iterator getRandomLabyrinth(); // получить случайный член популяции
    ~Population() = default;
private:
    static const int max_size = 1048576 * 5;
    static const int max_files = 3;
    static std::shared_ptr<spdlog::logger> logger;
    void refreshPopulationSize();
    void shrinkPopulation();
    int maxPopulationSize = 1000;
    static const int initialPopulationSize = 100;
    std::set<Labyrinth> population;
    int populationSize;
};



#endif //POPULATION_H
