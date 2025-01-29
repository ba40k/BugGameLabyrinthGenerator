//
// Created by radamir on 29.01.25.
//

#ifndef LABYRINTH_H
#define LABYRINTH_H

//  Этот класс будет использоваться в генетическом алгоритме, так что не удивляйтесь размножению лабиринтов

class Labyrinth {
public:
    Labyrinth();  // создаёт случайный лабиринт
    Labyrinth(const Labyrinth &other); // этот конструктор и еще 4 ниже - правило пяти
    Labyrinth(Labyrinth &&other) noexcept;
    Labyrinth &operator=(const Labyrinth &other);
    Labyrinth &operator=(Labyrinth &&other) noexcept;
    const void showLabyrinth() const; // отображение лабиринта
    [[nodiscard]] bool isPassable() const; // проверка лабиринта на проходимость
    [[nodiscard]] int score() const; // узнать счет этого лабиринта
    void setCell(int x, int y, char value); // установить указанное значение в выбранной клетке
    Labyrinth getDescendant(Labyrinth &partner); // получить потомка 
private:
    char** labyrinth;
    const int LABYRINTH_WIDTH = 30;
    const int LABYRINTH_HEIGHT = 20;
    const int frameThickness = 1;
    ~Labyrinth();
};



#endif //LABYRINTH_H
