//
// Created by radamir on 29.01.25.
//

#include "Generator.h"
#include "spdlog/spdlog.h"
Generator::Generator() : generator(std::random_device{}()), distribution(MIN_RANDOM_NUMB, MAX_RANDOM_NUMB) {
    spdlog::info("Enterpoint| Generator::Generator()");
    spdlog::info("End| Generator::Generator()");
}
Generator::Generator(const int seed, const int min, const int max) {
    spdlog::info("Enterpoint| Generator::Generator(int seed, int min, int max)");
    if (min > max) {
        spdlog::error("Generator::Generator: min > max");
        throw std::invalid_argument("min > max");
    }
    MIN_RANDOM_NUMB = min;
    MAX_RANDOM_NUMB = max;
    distribution = std::uniform_int_distribution<int>(min, max);
    generator = std::mt19937(seed);
    spdlog::info("End| Generator::Generator(int seed, int min, int max)");
}
bool Generator::getRandomBool() {
    spdlog::info("Enterpoint| Generator::getRandomBool()");
    spdlog::info("End| Generator::getRandomBool()");
    return distribution(generator)%2;
}
int Generator::getRandomInt() {
    spdlog::info("Enterpoint| Generator::getRandomInt()");
    spdlog::info("End| Generator::getRandomInt()");
    return distribution(generator);
}
int Generator::getRandomInt(int min, int max) {
    if (min > max) {
        spdlog::error("Enterpoint| Generator::getRandomInt(int min, int max) -- min > max");
        throw std::invalid_argument("min > max");
    }
    if (max < MIN_RANDOM_NUMB || min > MAX_RANDOM_NUMB) {
        spdlog::error("Enterpoint| Generator::getRandomInt(int min, int max) -- CAN'T GENERATE NUMBER IN THAT INTERVAL");
        throw std::invalid_argument("NO NUMBERS IN THAT INTERVAL");
    }
    if (min < MAX_RANDOM_NUMB && max > MIN_RANDOM_NUMB) {
        min = MIN_RANDOM_NUMB;
        spdlog::warn("LOGIC| Generator::getRandomInt(int min, int max) -- ARGUMENT MIN LESS THEN CLASS MIN");
    }
    if (max > MAX_RANDOM_NUMB) {
        max = MAX_RANDOM_NUMB;
        spdlog::warn("LOGIC| Generator::::getRandomInt(int min, int max) -- ARGUMENT MAX BIGGER THEN CLASS MAX");
    }
    spdlog::info("Enterpoint| Generator::getRandomInt(int min, int max)");
    spdlog::info("End| Generator::getRandomInt(int min, int max)");
    return distribution(generator)%(max - min + 1) + min; // в этой строке мы по сути генерируем индекс числа из заданного диапазона и возвращаем это число
}
int Generator::getMaxRandomNumb() const {
    spdlog::info("Enterpoint| Generator::getMaxRandomNumb()");
    spdlog::info("End| Generator::getMaxRandomNumb()");
    return MAX_RANDOM_NUMB;
}
int Generator::getMinRandomNumb() const {
    spdlog::info("Enterpoint| Generator::getMinRandomNumb()");
    spdlog::info("End| Generator::getMinRandomNumb()");
    return MIN_RANDOM_NUMB;
}
void Generator::setMaxRandomNumb(const int max) {
    spdlog::info("Enterpoint| Generator::setMaxRandomNumb(int max)");
    MAX_RANDOM_NUMB = max;
    spdlog::info("End| Generator::setMaxRandomNumb(int max)");
}
void Generator::setMinRandomNumb(const int min) {
    spdlog::info("Enterpoint| Generator::setMinRandomNumb(int min)");
    MIN_RANDOM_NUMB = min;
    spdlog::info("End| Generator::setMinRandomNumb(int min)");
}
