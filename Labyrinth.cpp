//
// Created by radamir on 29.01.25.
//

#include "Labyrinth.h"
#include <queue>

#include "Generator.h"

std::vector<std::pair<int,int>> Labyrinth::moves= {{+1,0},{0,+1},{-1,0},{0,-1}};
std::shared_ptr<spdlog::logger> Labyrinth::logger = spdlog::rotating_logger_mt("LabyrinthLogger", "../../logs/LabyrinthLog.txt", max_size, max_files);
void Labyrinth::setCell(int x, int y, char ch) {
    logger->info("Entrypoint| void Labyrinth::setCell(int x,int y,char ch");
    if (!isBelongsToLabyrinth(x, y)) {
        throw std::out_of_range("Labyrinth::setCell: x is out of range");
    }
    labyrinth[y][x] = ch;
    logger->info("End| void Labyrinth::setCell(int x,int y,char ch);\n");
}
Labyrinth::Labyrinth() {
    logger->info("Entrypoint| Labyrinth::Labyrinth()\n");
    labyrinth.resize(LABYRINTH_HEIGHT,std::vector<char>(LABYRINTH_WIDTH,floorSymbol)); // создали пустой лабиринт, без рамки
    // Изначально мы выбираем максимальное число клеток, которые могут быть сделаны стенами
    constexpr int MAX_WALLS_NUMBER = 5;
    Generator generator; // генератор случайных объектов
    const int wallsNumber = generator.getRandomInt(0, MAX_WALLS_NUMBER); //  определяем сколько стен будет построено
    for (int i =0;i<wallsNumber;i++) {
        auto wall = generator.getRandomPoint(LABYRINTH_WIDTH - 1, LABYRINTH_HEIGHT - 1);
        if (wall == std::make_pair(0,0)) { // нельзя блокировать точку, где жук изначально
            continue;
        }
        labyrinth[wall.second][wall.first]='#';
    }
    logger->info("End| Labyrinth::Labyrinth()\n");

}
bool Labyrinth::isBelongsToLabyrinth(const int x, const int y) {
    logger->info("Entrypoint| Labyrinth::bool isBelongsToLabyrinth(int x, int y) const\n");
    if (x<0
        || y <0
        || x > LABYRINTH_WIDTH -1 // проверка происходит без учета рамки
        || y > LABYRINTH_HEIGHT-1) {
        logger->info("End| Labyrinth::bool isBelongsToLabyrinth(int x, int y) const\n");
        return false;
    }
    logger->info("End| Labyrinth::bool isBelongsToLabyrinth(int x, int y) const\n");
    return true;
}

bool Labyrinth::isPassable(const int x, const int y) const {
    logger->info("Entrypoint| Labyrinth::bool isPassable(int x, int y) const\n");
    if (!isBelongsToLabyrinth(x, y)) {
        logger->error("OUT OF RANGE| Labyrinth::bool isPassable(int x, int y) const\n");
        throw std::out_of_range("Labyrinth::isPassable\n");
    }
    logger->info("End| Labyrinth::bool isPassable(int x, int y) const\n");
    return labyrinth[y][x]==floorSymbol;
}
bool Labyrinth::isPassable() const {
    logger->info("Entrypoint| Labyrinth::bool isPassable() const\n");
    std::queue<std::pair<int,int>> points;
    std::vector<std::vector<short>> visited(LABYRINTH_HEIGHT, std::vector<short>(LABYRINTH_WIDTH,0));
    if (!isPassable(0,0)) {
        return false;
    }
    points.emplace(0,0); // точка старта, {1,1} потому что не забываем про рамку
    visited[0][0]=1;
    while (!points.empty()) {
        auto from = points.front(); // запоминаем точку из которой будем сейчас ходить
        logger->trace("BFS | bool Labyrinth::isPassable() const -- Point is " + std::to_string(from.first) + " " + std::to_string(from.second) + "\n");
        points.pop(); // удаляем её
        for (auto nextMove : Labyrinth::moves) {
            auto to = from;
            to.first += nextMove.first;
            to.second += nextMove.second;
            if (isBelongsToLabyrinth(to.first, to.second)
                &&  isPassable(to.first, to.second)
                    && !visited[to.second][to.first]) {
                points.emplace(to.first, to.second);
                visited[to.second][to.first] = 1;
                    }
        }
    }
    logger->info("End| Labyrinth:: isPassable() const\n");
    return visited[LABYRINTH_HEIGHT-1][LABYRINTH_WIDTH-1];
}
char Labyrinth::getCell(int x, int y) const {
    if (!isBelongsToLabyrinth(x, y)) {
        logger->error("Logic| char Labyrinth::getCell(int x, int y) const \n");
        throw std::out_of_range("Labyrinth::getCell\n");
    }
    logger->info("Entrypoint| Labyrinth::getCell(int x, int y) const\n");
    logger->info("End| Labyrinth::getCell(int x, int y) const\n");
    return labyrinth[y][x];
}
void Labyrinth::showLabyrinth(std::ostream& out) const {
    logger->info("Entrypoint|void Labyrinth::showLabyrinth(std::ostream& out) showLabyrinth() const\n");
    for (int i =0;i<LABYRINTH_HEIGHT;i++) {
        for (int j=0;j<LABYRINTH_WIDTH;j++) {
            out<<labyrinth[i][j];
        }
        out<<'\n';
    }
    logger->info("End| void Labyrinth::showLabyrinth(std::ostream& out) showLabyrinth() const\n");
}
char Labyrinth::getFloorSymbol() const {
    
}
