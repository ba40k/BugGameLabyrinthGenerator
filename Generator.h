//
// Created by radamir on 29.01.25.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include <utility>
#include <random>
class Generator {
public:
    Generator(); // дефолтный генератор, использует стдшный рандом
    Generator(int seed, int min, int max); // устанавливает выбранные рамки и сид
    Generator(const Generator& other) = default; // это и ниже - правило пяти
    Generator& operator=(const Generator& other) = delete;
    Generator(Generator&& other) noexcept = delete;
    Generator& operator=(Generator&& other) noexcept = delete ;
    std::pair<int,int> getRandomPoint(int LIMIT_X, int LIMIT_Y); // дает случайную точку с координатами от нуля до заданных пределов
    bool getRandomBool(); //  дает случайный бул
    int getRandomInt(); // дает случайный инт
    int getRandomInt(int min, int max);
    void setMinRandomNumb(int min); // установить нижнюю границу рандома
    void setMaxRandomNumb(int max);// установить верхнюю границу рандома
    [[nodiscard]] int getMinRandomNumb() const;// узнать нижнюю границу рандома
    [[nodiscard]] int getMaxRandomNumb() const;// узнать верхнюю границу рандома
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
