//
// Created by radamir on 29.01.25.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include <utility>
#include <random>
class Generator {
public:
    Generator();
    Generator(int seed, int min, int max);
    Generator(const Generator& other) = default;
    Generator& operator=(const Generator& other) = delete;
    Generator(Generator&& other) noexcept = delete;
    Generator& operator=(Generator&& other) noexcept = delete ;
    std::pair<int,int> getRandomPoint(int LIMIT_X, int LIMIT_Y); // дает случайную точку с координатами от нуля до заданных пределов
    bool getRandomBool(); //  дает случайный бул
    int getRandomInt(); // дает случайный инт
    ~Generator() = default;
private:
    int MIN_RANDOM_NUMB = 0;
    int MAX_RANDOM_NUMB = 2000000000;
    // Создание объекта генератора случайных чисел на основе mt19937
    std::mt19937 generator;
    // Определение диапазона распределения (например, от 0 до 100)
    std::uniform_int_distribution<int> distribution;
};



#endif //GENERATOR_H
