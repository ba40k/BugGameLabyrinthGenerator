//
// Created by radamir on 29.01.25.
//

#include "Labyrinth.h"
bool Labyrinth::isBelongsToLabyrinth(int x, int y) const {
    spdlog::info("Entrypoint: Labyrinth::bool isBelongsToLabyrinth(int x, int y) const");
    if (x<0
        || y <0
        || x > LABYRINTH_WIDTH + FRAME_THICKNESS-1
        || y > LABYRINTH_HEIGHT + FRAME_THICKNESS-1) {
        spdlog::error("OUT OF RANGE IN: Labyrinth::bool isBelongsToLabyrinth(int x, int y) const");
        throw std::out_of_range("Labyrinth::isBelongsToLabyrinth");
    }
    spdlog::info("Returned: Labyrinth::bool isBelongsToLabyrinth(int x, int y) const");
    return true;
}

bool Labyrinth::isFloor(int x, int y) const {
    spdlog::info("Labyrinth::bool isFloor(int x, int y) const");

}

