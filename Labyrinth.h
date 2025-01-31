//
// Created by radamir on 29.01.25.
//

#ifndef LABYRINTH_H
#define LABYRINTH_H
#include <vector>
#include <utility>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
//  Этот класс будет использоваться в генетическом алгоритме, так что не удивляйтесь размножению лабиринтов

class Labyrinth {
public:
    Labyrinth();  // создаёт случайный(или не очень) лабиринт
    Labyrinth(const Labyrinth &other); // этот конструктор и еще 4 ниже - правило пяти
    Labyrinth(Labyrinth &&other) noexcept;
    Labyrinth &operator=(const Labyrinth &other);
    Labyrinth &operator=(Labyrinth &&other) noexcept;
    void showLabyrinth(std::ostream& out) const; // отображение лабиринта
    [[nodiscard]] bool isPassable() const; // проверка лабиринта на проходимость
    [[nodiscard]] int score() const; // узнать счет этого лабиринта
    void setCell(int x, int y, char value); // установить указанное значение в выбранной клетке
    Labyrinth getDescendant(Labyrinth &partner); // получить потомка
    [[nodiscard]] static bool isBelongsToLabyrinth(int x, int y) ; // проверка на то попадает ли точка в лабиринт
    [[nodiscard]] bool isPassable(int x, int y) const; // этот метод - проверка на то проходима ли клетка
    [[nodiscard]] char getCell(int x, int y) const;
    [[nodiscard]] char getWallSymbol() const;
    [[nodiscard]] char getFloorSymbol() const;
    ~Labyrinth() = default;
private:
    static const int max_size = 1048576 * 5;
    static const int max_files = 3;
    static std::shared_ptr<spdlog::logger> logger;
    std::vector<std::vector<char>> labyrinth;  // лабиринт хранится без рамки
    static std::vector<std::pair<int, int>> moves; // задает то, в каких направлениях можно ходить по лабиринту
    static constexpr int LABYRINTH_WIDTH = 30;
    static constexpr int LABYRINTH_HEIGHT = 20;
    static constexpr int  FRAME_THICKNESS = 1;
    const char wallSymbol = '#';
    const char floorSymbol = '.';

};
#endif //LABYRINTH_H
