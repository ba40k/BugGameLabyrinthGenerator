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
    std::string fileName = "output" + std::to_string(number) + ".txt";
    std::ofstream out(fileName);
    Population<Labyrinth> pop(20);
    int iterations = 50;
    while (iterations--){
        out.seekp(0);
        pop.mutate();
        pop.refreshGeneration();
        pop.mutate();
        out<<pop.getBestLabyrinth().getScore()<<'\n';
        pop.getBestLabyrinth().printLabyrinth(out);
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
    task1.join();
    task2.join();
    task3.join();
    task4.join();
    task5.join();
    task6.join();
}
