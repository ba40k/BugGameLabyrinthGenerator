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
    std::set<Labyrinth>::iterator getRandomLabyrinth(); // получить случайный член популяции
    ~Population() = default;
private:
    void shrinkPopulation();
    const int maxPopulationSize = 1000;
    static const int initialPopulationSize = 100;
    std::set<Labyrinth> population;
    int populationSize;
};



#endif //POPULATION_H
