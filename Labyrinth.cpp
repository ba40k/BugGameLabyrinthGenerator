//
// Created by radamir on 29.01.25.
//

#include "Labyrinth.h"
#include <queue>

#include "Generator.h"
std::vector<std::pair<int,int>> Labyrinth::moves= {{+1,0},{0,+1},{-1,0},{0,-1}};
void Labyrinth::setCell(int x, int y, char ch) {
    spdlog::info("Entrypoint| void Labyrinth::setCell(int x,int y,char ch");
    if (!isBelongsToLabyrinth(x, y)) {
        throw std::out_of_range("Labyrinth::setCell: x is out of range");
    }
    labyrinth[y][x] = ch;
    spdlog::info("End| void Labyrinth::setCell(int x,int y,char ch);\n");
}
Labyrinth::Labyrinth() {
    spdlog::info("Entrypoint| Labyrinth::Labyrinth()\n");
    labyrinth.resize(LABYRINTH_HEIGHT,std::vector<char>(LABYRINTH_WIDTH,floorSymbol)); // создали пустой лабиринт, без рамки
    // Изначально мы выбираем максимальное число клеток, которые могут быть сделаны стенами
    constexpr int MAX_WALLS_NUMBER = 5;
    Generator generator; // генератор случайных объектов
    const int wallsNumber = generator.getRandomInt(0, MAX_WALLS_NUMBER); //  определяем сколько стен будет построено
    for (int i =0;i<wallsNumber;i++) {
        auto wall = generator.getRandomPoint(LABYRINTH_WIDTH - 1, LABYRINTH_HEIGHT - 1);
        if (wall == std::make_pair(0,0)) { // нельзя блокировать точку где жук изначально
            continue;
        }
        labyrinth[wall.second][wall.first]='#';
    }
    spdlog::info("End| Labyrinth::Labyrinth()\n");

}
bool Labyrinth::isBelongsToLabyrinth(const int x, const int y) {
    spdlog::info("Entrypoint| Labyrinth::bool isBelongsToLabyrinth(int x, int y) const\n");
    if (x<0
        || y <0
        || x > LABYRINTH_WIDTH -1 // проверка происходит без учета рамки
        || y > LABYRINTH_HEIGHT-1) {
        spdlog::info("End| Labyrinth::bool isBelongsToLabyrinth(int x, int y) const\n");
        return false;
    }
    spdlog::info("End| Labyrinth::bool isBelongsToLabyrinth(int x, int y) const\n");
    return true;
}

bool Labyrinth::isPassable(const int x, const int y) const {
    spdlog::info("Entrypoint| Labyrinth::bool isPassable(int x, int y) const\n");
    if (!isBelongsToLabyrinth(x, y)) {
        spdlog::error("OUT OF RANGE| Labyrinth::bool isPassable(int x, int y) const\n");
        throw std::out_of_range("Labyrinth::isPassable\n");
    }
    spdlog::info("End| Labyrinth::bool isPassable(int x, int y) const\n");
    return labyrinth[y][x]==floorSymbol;
}
bool Labyrinth::isPassable() const {
    spdlog::info("Entrypoint| Labyrinth::bool isPassable() const\n");
    std::queue<std::pair<int,int>> points;
    std::vector<std::vector<short>> visited(LABYRINTH_HEIGHT, std::vector<short>(LABYRINTH_WIDTH,0));
    points.emplace(0,0); // точка старта, {1,1} потому что не забываем про рамку
    visited[0][0]=1;
    while (!points.empty()) {
        auto from = points.front(); // запоминаем точку из которой будем сейчас ходить
        points.pop(); // удаляем её
        for (auto nextMove : Labyrinth::moves) {
            auto to = from;
            to.first += nextMove.first;
            to.second += nextMove.second;
            if (isBelongsToLabyrinth(to.first, to.second)
                &&  isPassable(to.first, to.second
                    && !visited[to.first][to.second])) {
                points.emplace(to.first, to.second);
                visited[to.first][to.second] = 1;
                    }
        }
    }
    spdlog::info("End| Labyrinth:: isPassable() const\n");
    return visited[LABYRINTH_HEIGHT-1][LABYRINTH_WIDTH-1];
}
