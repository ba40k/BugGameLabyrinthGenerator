//
// Created by radamir on 29.01.25.
//

#include "Generator.h"
#include "spdlog/spdlog.h"
Generator::Generator() : generator(std::random_device{}()), distribution(MIN_RANDOM_NUMB, MAX_RANDOM_NUMB) {
    spdlog::info("Enterpoint| Generator::Generator()\n");
    spdlog::info("End| Generator::Generator()\n");
}
Generator::Generator(const int seed, const int min, const int max) {
    spdlog::info("Enterpoint| Generator::Generator(int seed, int min, int max)\n");
    if (min > max) {
        spdlog::error("Logic|Generator::Generator: min > max\n");
        throw std::invalid_argument("min > max");
    }
    MIN_RANDOM_NUMB = min;
    MAX_RANDOM_NUMB = max;
    distribution = std::uniform_int_distribution<int>(min, max);
    generator = std::mt19937(seed);
    spdlog::info("End| Generator::Generator(int seed, int min, int max)\n");
}
bool Generator::getRandomBool() {
    spdlog::info("Enterpoint| Generator::getRandomBool()\n");
    spdlog::info("End| Generator::getRandomBool()\n");
    return distribution(generator)%2;
}
int Generator::getRandomInt() {
    spdlog::info("Enterpoint| Generator::getRandomInt()\n");
    spdlog::info("End| Generator::getRandomInt()\n");
    return distribution(generator);
}
int Generator::getRandomInt(int min, int max) {
    if (min > max) {
        spdlog::error("Enterpoint| Generator::getRandomInt(int min, int max) -- min > max\n");
        throw std::invalid_argument("min > max");
    }
    if (max < MIN_RANDOM_NUMB || min > MAX_RANDOM_NUMB) {
        spdlog::error("Enterpoint| Generator::getRandomInt(int min, int max) -- CAN'T GENERATE NUMBER IN THAT INTERVAL\n");
        throw std::invalid_argument("NO NUMBERS IN THAT INTERVAL");
    }
    if (min < MAX_RANDOM_NUMB && max > MIN_RANDOM_NUMB) {
        min = MIN_RANDOM_NUMB;
        spdlog::warn("Logic| Generator::getRandomInt(int min, int max) -- ARGUMENT MIN LESS THEN CLASS MIN\n");
    }
    if (max > MAX_RANDOM_NUMB) {
        max = MAX_RANDOM_NUMB;
        spdlog::warn("Logic| Generator::::getRandomInt(int min, int max) -- ARGUMENT MAX BIGGER THEN CLASS MAX\n");
    }
    spdlog::info("Enterpoint| Generator::getRandomInt(int min, int max)\n");
    spdlog::info("End| Generator::getRandomInt(int min, int max)\n");
    return distribution(generator)%(max - min + 1) + min; // в этой строке мы по сути генерируем индекс числа из заданного диапазона и возвращаем это число
}
int Generator::getMaxRandomNumb() const {
    spdlog::info("Enterpoint| Generator::getMaxRandomNumb()\n");
    spdlog::info("End| Generator::getMaxRandomNumb()\n");
    return MAX_RANDOM_NUMB;
}
int Generator::getMinRandomNumb() const {
    spdlog::info("Enterpoint| Generator::getMinRandomNumb()\n");
    spdlog::info("End| Generator::getMinRandomNumb()\n");
    return MIN_RANDOM_NUMB;
}
void Generator::setMaxRandomNumb(const int max) {
    spdlog::info("Enterpoint| Generator::setMaxRandomNumb(int max)\n");
    MAX_RANDOM_NUMB = max;
    spdlog::info("End| Generator::setMaxRandomNumb(int max)\n");
}
void Generator::setMinRandomNumb(const int min) {
    spdlog::info("Enterpoint| Generator::setMinRandomNumb(int min)\n");
    MIN_RANDOM_NUMB = min;
    spdlog::info("End| Generator::setMinRandomNumb(int min)\n");
}
std::pair<int, int> Generator::getRandomPoint(const int LIMIT_X,const  int LIMIT_Y) {
    spdlog::info("Enterpoint| Generator::getRandomPoint(int LIMIT_X, int LIMIT_Y)\n");
    if (LIMIT_X < 0 || LIMIT_Y<0) {
        spdlog::error("Logic| Generator::getRandomPoint(int LIMIT_X, int LIMIT_Y) -- NO NUMBERS IN THAT INTERVAL\n");
        throw std::invalid_argument("NO NUMBERS IN THAT INTERVAL");
    }
    int x = getRandomInt(0, LIMIT_X);
    int y = getRandomInt(0, LIMIT_Y);
    spdlog::info("End| Generator::getRandomPoint(int LIMIT_X, int LIMIT_Y)\n");
    return std::make_pair(x, y);
}
