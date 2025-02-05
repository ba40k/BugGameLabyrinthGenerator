//
// Created by radamir on 29.01.25.
//

#include "Generator.h"
#include "spdlog/spdlog.h"
#include <chrono>
std::shared_ptr<spdlog::logger> Generator::logger = spdlog::rotating_logger_mt("GeneratorLogger", "../../logs/GeneratorLog.txt", max_size, max_files);
Generator::Generator() : generator(std::chrono::steady_clock::now().time_since_epoch().count()), distribution(MIN_RANDOM_NUMB, MAX_RANDOM_NUMB) {
    logger->info("Enterpoint| Generator::Generator()\n");
    logger->info("End| Generator::Generator()\n");
}
Generator::Generator(const int seed, const int min, const int max) {
    logger->info("Enterpoint| Generator::Generator(int seed, int min, int max)\n");
    if (min > max) {
        logger->error("Logic|Generator::Generator: min > max\n");
        throw std::invalid_argument("min > max");
    }
    MIN_RANDOM_NUMB = min;
    MAX_RANDOM_NUMB = max;
    distribution = std::uniform_int_distribution<int>(min, max);
    generator = std::mt19937(seed);
    logger->info("End| Generator::Generator(int seed, int min, int max)\n");
}
bool Generator::getRandomBool()  {
    logger->info("Enterpoint| Generator::getRandomBool()\n");
    logger->info("End| Generator::getRandomBool()\n");
    return distribution(generator)%2;
}
int Generator::getRandomInt() {
    logger->info("Enterpoint| Generator::getRandomInt()\n");
    logger->info("End| Generator::getRandomInt()\n");
    return distribution(generator);
}
int Generator::getRandomInt(int min, int max) {
    if (min > max) {
        logger->error("Enterpoint| Generator::getRandomInt(int min, int max) -- min > max\n");
        throw std::invalid_argument("min > max");
    }
    if (max < MIN_RANDOM_NUMB || min > MAX_RANDOM_NUMB) {
        logger->error("Enterpoint| Generator::getRandomInt(int min, int max) -- CAN'T GENERATE NUMBER IN THAT INTERVAL\n");
        throw std::invalid_argument("NO NUMBERS IN THAT INTERVAL");
    }
    if (min < MIN_RANDOM_NUMB) {
        min = MIN_RANDOM_NUMB;
        logger->warn("Logic| Generator::getRandomInt(int min, int max) -- ARGUMENT MIN LESS THEN CLASS MIN\n");
    }
    if (max > MAX_RANDOM_NUMB) {
        max = MAX_RANDOM_NUMB;
        logger->warn("Logic| Generator::::getRandomInt(int min, int max) -- ARGUMENT MAX BIGGER THEN CLASS MAX\n");
    }
    logger->info("Enterpoint| Generator::getRandomInt(int min, int max)\n");
    logger->info("End| Generator::getRandomInt(int min, int max)\n");
    return distribution(generator)%(max - min + 1) + min; // в этой строке мы по сути генерируем индекс числа из заданного диапазона и возвращаем это число
}
int Generator::getMaxRandomNumb() const {
    logger->info("Enterpoint| Generator::getMaxRandomNumb()\n");
    logger->info("End| Generator::getMaxRandomNumb()\n");
    return MAX_RANDOM_NUMB;
}
int Generator::getMinRandomNumb() const {
    logger->info("Enterpoint| Generator::getMinRandomNumb()\n");
    logger->info("End| Generator::getMinRandomNumb()\n");
    return MIN_RANDOM_NUMB;
}
void Generator::setMaxRandomNumb(const int max) {
    logger->info("Enterpoint| Generator::setMaxRandomNumb(int max)\n");
    MAX_RANDOM_NUMB = max;
    logger->info("End| Generator::setMaxRandomNumb(int max)\n");
}
void Generator::setMinRandomNumb(const int min) {
    logger->info("Enterpoint| Generator::setMinRandomNumb(int min)\n");
    MIN_RANDOM_NUMB = min;
    logger->info("End| Generator::setMinRandomNumb(int min)\n");
}
std::pair<int, int> Generator::getRandomPoint(const int LIMIT_X,const  int LIMIT_Y) {
    logger->info("Enterpoint| Generator::getRandomPoint(int LIMIT_X, int LIMIT_Y)\n");
    if (LIMIT_X < 0 || LIMIT_Y<0) {
        logger->error("Logic| Generator::getRandomPoint(int LIMIT_X, int LIMIT_Y) -- NO NUMBERS IN THAT INTERVAL\n");
        throw std::invalid_argument("NO NUMBERS IN THAT INTERVAL");
    }
    int x = getRandomInt(0, LIMIT_X);
    int y = getRandomInt(0, LIMIT_Y);
    logger->info("End| Generator::getRandomPoint(int LIMIT_X, int LIMIT_Y)\n");
    return std::make_pair(x, y);
}
std::vector<std::vector<char> > Generator::getRandomMask(int height, int width)  {
    logger->info("Enterpoint| Generator::getRandomMask(int height, int width)\n");
    std::vector<std::vector<char> > mask(height, std::vector<char>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            getRandomBool()==1?mask[i][j]='#':mask[i][j]='.';
        }
    }
    return mask;
}
