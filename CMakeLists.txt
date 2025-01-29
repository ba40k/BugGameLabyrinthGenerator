cmake_minimum_required(VERSION 3.29)
project(BugGameLabyrinthGenerator)

set(CMAKE_CXX_STANDARD 20)

add_executable(generator main.cpp)
include_directories(spdlog/include)
add_library(generator_lib STATIC Labyrinth.cpp Generator.cpp)

target_link_libraries(generator generator_lib)

