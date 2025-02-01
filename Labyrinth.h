//
// Created by radamir on 29.01.25.
//

#ifndef LABYRINTH_H
#define LABYRINTH_H
#include <vector>
#include <utility>
#include <spdlog/spdlog.h>
#include <iostream>
#include <spdlog/sinks/rotating_file_sink.h>
//  Этот класс будет использоваться в генетическом алгоритме, так что не удивляйтесь размножению лабиринтов

class Labyrinth {
public:
    Labyrinth();  // создаёт случайный(или не очень) лабиринт
    explicit Labyrinth(int wallsNumber); //  передаем количество стен, если хотим какое-то конкретное (например 0)
    Labyrinth(const Labyrinth &other) = default; // этот конструктор и еще 3 ниже - правило пяти
    Labyrinth(Labyrinth &&other) noexcept = default;
    Labyrinth &operator=(const Labyrinth &other);
    Labyrinth &operator=(Labyrinth &&other) noexcept;
    bool operator<(const Labyrinth &other) const; // сравнивает лабиринты по их скору, нужно для хранения в std::set
    void clear(); // делает лабиринт пустым
    void printLabyrinth(std::ostream& out = std::cout) const; // отображение лабиринта
    [[nodiscard]] bool isPassable() const; // проверка лабиринта на проходимость
    [[nodiscard]] int getScore() const; //  здесь мы не вычисляем счет, а возвращаем то, что уже было вычислено
    void setCell(int x, int y, char value); // установить указанное значение в выбранной клетке
    [[nodiscard]] Labyrinth getDescendant(const Labyrinth &partner) const; // получить потомка
    [[nodiscard]] static bool isBelongsToLabyrinth(int x, int y) ; // проверка на то попадает ли точка в лабиринт
    [[nodiscard]] bool isPassable(int x, int y) const; // этот метод - проверка на то проходима ли клетка
    [[nodiscard]] char getCell(int x, int y) const; // получить то, что хранится в клетке
    [[nodiscard]] char getWallSymbol() const; // узнать символ стены
    [[nodiscard]] char getFloorSymbol() const; // узнать символ пола
    void mutation();
    ~Labyrinth() = default;
private:
    [[nodiscard]] int calculateScore() const; // вычислить счет этого лабиринта
    void printFrameHorizontalPart(std::ostream& out = std::cout) const; // вывод горизонтальной части рамки
    void refreshScore();
    int score;
    static const int max_size = 1048576 * 5;
    static const int max_files = 3;
    static std::shared_ptr<spdlog::logger> logger;
    std::vector<std::vector<char>> labyrinth;  // лабиринт хранится без рамки
    static std::vector<std::pair<int, int>> moves; // задает то, в каких направлениях можно ходить по лабиринту
    static constexpr int LABYRINTH_WIDTH = 29;
    static constexpr int LABYRINTH_HEIGHT = 19;
    static constexpr int  FRAME_THICKNESS = 1;
    const char wallSymbol = '#';
    const char floorSymbol = '.';
    const int acceptableScore = 1e5; // достаточный для меня счет
    const int inf = 1e9;
};
#endif //LABYRINTH_H
