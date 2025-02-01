//
// Created by radamir on 29.01.25.
//
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <fstream>
#include "Labyrinth.h"
#include "Population.h"
int main() {
    std::ofstream out("../output.txt");
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
