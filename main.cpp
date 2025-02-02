//
// Created by radamir on 29.01.25.
//
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <fstream>
#include "Labyrinth.h"
#include "Population.h"
#include <string>
#include <thread>
void task(int number) {
    std::string fileName = "../res/output" + std::to_string(number) + ".txt";
    std::ofstream out(fileName);
    Population<Labyrinth> pop(50);
    pop.setMaxPopulationSize(100);
    Labyrinth bestLabyrinth;
    int iterations = 5000;
    while (iterations--){
        out.seekp(0);
        pop.mutate();
        pop.mutate();
        pop.mutate();
        if (iterations % 100 == 0) {
            pop.refreshGeneration();
        }
        if (pop.getBestLabyrinth().getScore() > bestLabyrinth.getScore()) {
            bestLabyrinth = pop.getBestLabyrinth();
        }
        out<<bestLabyrinth.getScore()<<'\n';
        bestLabyrinth.printLabyrinth(out);
        out<<'\n';
        out.flush();
    }
}
int main() {
    std::thread task1(task, 1);
    std::thread task2(task, 2);
    std::thread task3(task, 3);
    std::thread task4(task, 4);
    std::thread task5(task, 5);
    std::thread task6(task, 6);
    std::thread task7(task, 7);
    std::thread task8(task, 8);
    std::thread task9(task, 9);
    std::thread task10(task, 10);
    std::thread task11(task, 11);
    task1.join();
    task2.join();
    task3.join();
    task4.join();
    task5.join();
    task6.join();
    task7.join();
    task8.join();
    task9.join();
    task10.join();
    task11.join();
}
