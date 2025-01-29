//
// Created by radamir on 29.01.25.
//

#include "Labyrinth.h"
#include <queue>
std::vector<std::pair<int,int>> Labyrinth::moves= {{+1,0},{0,+1},{-1,0},{0,-1}};
bool Labyrinth::isBelongsToLabyrinth(const int x, const int y) {
    spdlog::info("Entrypoint| Labyrinth::bool isBelongsToLabyrinth(int x, int y) const\n");
    if (x<0
        || y <0
        || x > LABYRINTH_WIDTH + FRAME_THICKNESS-1
        || y > LABYRINTH_HEIGHT + FRAME_THICKNESS-1) {
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
    return labyrinth[y][x]=='.';
}
bool Labyrinth::isPassable() const {
    spdlog::info("Entrypoint| Labyrinth::bool isPassable() const\n");
    std::queue<std::pair<int,int>> points;
    std::vector<std::vector<short>> visited(LABYRINTH_HEIGHT+FRAME_THICKNESS*2, std::vector<short>(LABYRINTH_WIDTH+FRAME_THICKNESS*2,0));
    points.emplace(1,1); // точка старта, {1,1} потому что не забываем про рамку
    visited[1][1]=1;
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
    return visited[LABYRINTH_HEIGHT][LABYRINTH_WIDTH];
}