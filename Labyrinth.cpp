//
// Created by radamir on 29.01.25.
//

#include "Labyrinth.h"
#include <queue>

#include "Generator.h"
#include <algorithm>
#include <iostream>
#include <functional>

std::vector<std::pair<int,int>> Labyrinth::moves= {{+1,0},{0,+1},{-1,0},{0,-1}};
std::shared_ptr<spdlog::logger> Labyrinth::logger = spdlog::rotating_logger_mt("LabyrinthLogger", "../../logs/LabyrinthLog.txt", max_size, max_files);
void Labyrinth::setCell(int x, int y, char ch) {
    logger->info("Entrypoint| void Labyrinth::setCell(int x,int y,char ch");
    if (!isBelongsToLabyrinth(x, y)) {
        throw std::out_of_range("Labyrinth::setCell: x is out of range");
    }
    labyrinth[y][x] = ch;
    refreshScore();
    logger->info("End| void Labyrinth::setCell(int x,int y,char ch);\n");
}
void Labyrinth::refreshScore() {
    logger->info("Entrypoint| void Labyrinth::refreshScore();\n");
    score = calculateScore();
    logger->info("End| void Labyrinth::refreshScore();\n");
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
    score = calculateScore();
    logger->info("End| Labyrinth::Labyrinth()\n");

}
Labyrinth::Labyrinth(int wallsNumber) {
    logger->info("Entrypoint| Labyrinth::Labyrinth(int wallsNumber)\n");
    labyrinth.resize(LABYRINTH_HEIGHT,std::vector<char>(LABYRINTH_WIDTH,floorSymbol)); // создали пустой лабиринт, без рамки
    // Изначально мы выбираем максимальное число клеток, которые могут быть сделаны стенами
    constexpr int MAX_WALLS_NUMBER = 5;
    Generator generator; // генератор случайных объектов
    for (int i =0;i<wallsNumber;i++) {
        auto wall = generator.getRandomPoint(LABYRINTH_WIDTH - 1, LABYRINTH_HEIGHT - 1);
        if (wall == std::make_pair(0,0)) { // нельзя блокировать точку, где жук изначально
            continue;
        }
        labyrinth[wall.second][wall.first]='#';
    }
    score = calculateScore();
    logger->info("End| Labyrinth::Labyrinth(int wallsNumber)\n");

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
void Labyrinth::printFrameHorizontalPart( std::ostream &out) const {
    for (int i =0;i<FRAME_THICKNESS;i++) {
        for (int j=0;j<FRAME_THICKNESS;j++) {
            out<<'#';
        }
        for (int j=0;j<LABYRINTH_WIDTH;j++) {
            out<<'#';
        }
        for (int j=0;j<FRAME_THICKNESS;j++) {
            out<<'#';
        }
        out<<'\n';
    }
}
void Labyrinth::printLabyrinth(std::ostream& out) const {
    logger->info("Entrypoint| void Labyrinth::showLabyrinth(std::ostream& out)  const\n");

    printFrameHorizontalPart();
    auto printFrameVerticalPartHelper = [&out]() {
        for (int j=0;j<FRAME_THICKNESS;j++) {
            out<<'#';
        }
    };
    for (int i=0;i<LABYRINTH_HEIGHT;i++) {
        printFrameVerticalPartHelper();
        for (int j=0;j<LABYRINTH_WIDTH;j++) {
            out<<getCell(j,i);
        }
        printFrameVerticalPartHelper();
        out<<'\n';
    }
    printFrameHorizontalPart();
    logger->info("End| void Labyrinth::showLabyrinth(std::ostream& out) const\n");
}
char Labyrinth::getFloorSymbol() const {
     logger->info("Entrypoint| char Labyrinth::getFloorSymbol() const\n");
     logger->info("End| char Labyrinth::getFloorSymbol() const\n");
     return floorSymbol;
}
char Labyrinth::getWallSymbol() const {
    logger->info("Entrypoint| char Labyrinth::getWallSymbol() const\n");
    logger->info("End| char Labyrinth::getWallSymbol() const\n");
    return wallSymbol;
}
void Labyrinth::clear() {
    logger->info("Entrypoint| void Labyrinth::clear() const\n");
    for (int i =0;i<LABYRINTH_HEIGHT;i++) {
        for (int j=0;j<LABYRINTH_WIDTH;j++) {
            setCell(j,i,'.');
        }
    }
    score = 46; // небольшое ускорение, чтобы не обсчитывать это
    logger->info("End| void Labyrinth::clear() const\n");
}

int Labyrinth::calculateScore() const {
    //  ужасный код, это мое старое решение и я не хочу его переписывать
    logger->info("Entrypoint| int Labyrinth::score() const\n");
    if (!isPassable()) // если лабиринт непроходим, то мы это обозначаем бесконечно малым скорингом
    {
        logger->info("End| int Labyrinth::score() const\n");
        return -inf;
    }
    int matrix[LABYRINTH_HEIGHT][LABYRINTH_WIDTH];
    int score = - inf;
    for (int i=0; i<LABYRINTH_HEIGHT; ++i)
    {
        for (int j=0; j<LABYRINTH_WIDTH; ++j)
        {
            matrix[i][j] = 0;
        }
    }

    matrix[0][0] = 1;
    int i= 0;
    int j = 0;
    int orient = 2;
    int step =-1;
    std::vector<int> next(4,inf);
    std::vector<int> vals(4,inf);
    while (true)
    {
        step++;
        if (score>=acceptableScore)
        {
            // пока что для меня достаточно такого результата для лабиринта, поэтому чтобы не тормозить программу по его достижению завершаемся
            return inf;
        }
        if (i == LABYRINTH_HEIGHT-1 && j == LABYRINTH_WIDTH-1)
        {
            score = step;
            break;
        }
        std::fill(next.begin(), next.end(), inf);
        std::fill(vals.begin(), vals.end(), inf);
        int ind =0;
        for (auto el : moves)
        {
            int nextI = i + el.first;
            int nextJ = j + el.second;
            if (isBelongsToLabyrinth(nextJ,nextI) && isPassable(nextJ, nextI))
            {
                next[ind] = matrix[nextI][nextJ];
                vals[ind] = matrix[nextI][nextJ];
            }
            ind++;
        }
        std::sort(vals.begin(),vals.end());
        if (next[0]<next[1] && next[0]<next[2] && next[0]<next[3])
        {
            auto el = moves[0];
            orient = 0;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            continue;
        }
        if (next[1]<next[0] && next[1]<next[2] && next[1]<next[3])
        {
            auto el = moves[1];
            orient = 1;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            continue;
        }
        if (next[2]<next[0] && next[2]<next[1] && next[2]<next[3])
        {
            auto el = moves[2];
            matrix[i+el.first][j+el.second]++;
            orient = 2;
            i+=el.first;
            j+=el.second;
            continue;
        }
        if (next[3]<next[0] && next[3]<next[1] && next[3]<next[2])
        {
            auto el = moves[3];
            matrix[i+el.first][j+el.second]++;
            orient = 3;
            i+=el.first;
            j+=el.second;
            continue;
        }
        if (next[orient]!=1e9 && next[orient] == vals[0])
        {
            auto el = moves[orient];
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            continue;
        }
        if (next[0]!=1e9 && next[0] == vals[0])
        {
            auto el = moves[0];
            orient = 0;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            continue;
        }
        if (next[1]!=1e9 && next[1] == vals[0])
        {
            auto el = moves[1];
            orient = 1;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            continue;
        }
        if (next[2]!=1e9 && next[2] == vals[0])
        {
            auto el = moves[2];
            orient = 2;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            continue;
        }
        if (next[3]!=1e9 &&  next[3] == vals[0])
        {
            auto el = moves[3];
            orient = 3;
            matrix[i+el.first][j+el.second]++;
            i+=el.first;
            j+=el.second;
            continue;
        }
        break;
    }
    logger->info("End| int Labyrinth::score() const\n");
    return score;
}
int Labyrinth::getScore() const {
    logger->info("EntryPoint| Labyrinth::getScore()\n");
    logger->info("End| Labyrinth::getScore()\n");
    return score;
}
Labyrinth &Labyrinth::operator=(const Labyrinth &other) {
    logger->info("EnterPoint| Labyrinth::operator=()\n");
    if (this == &other) {
        logger->info("End| Labyrinth::operator=()\n");
        return *this;
    }
    score = other.score;
    labyrinth = other.labyrinth;
    logger->info("End| Labyrinth::operator=()\n");
    return *this;
}
Labyrinth Labyrinth::getDescendant(const Labyrinth &partner) const{
    logger->info("EntryPoint| Labyrinth::getDescendant()\n");
    Labyrinth descendant = *this;
    int maxNumberOfMutations = 7;
    Generator generator;
    int numberOfMutations = generator.getRandomInt(0,maxNumberOfMutations);
    for (int i =0;i<numberOfMutations;i++) {
        auto randomPoint = generator.getRandomPoint(LABYRINTH_WIDTH,LABYRINTH_HEIGHT);
        descendant.setCell(randomPoint.first,randomPoint.second,partner.getCell(randomPoint.first,randomPoint.second));
    }
    logger->info("End| Labyrinth::getDescendant()\n");
    return descendant;
}
bool Labyrinth::operator<(const Labyrinth &other) const {
    logger->info("EntryPoint| Labyrinth::operator<()\n");
    logger->info("End| Labyrinth::operator<()\n");
    return score < other.score;
}
void Labyrinth::mutation() {
    logger->info("EntryPoint| Labyrinth::mutation()\n");
    Generator generator;
    auto point = generator.getRandomPoint(LABYRINTH_WIDTH,LABYRINTH_HEIGHT);
    bool randomBool = generator.getRandomBool();
    (randomBool==1)?setCell(point.first,point.second,'#'):setCell(point.first,point.second,'.');
    logger->info("End| Labyrinth::mutation()\n");
}

