cmake_minimum_required(VERSION 3.14)
project(labyrinth-game)

add_subdirectory(../labyrinth-engine engine_build)
add_subdirectory(../labyrinth-content content_build)

add_executable(LabyrinthGame src/main.cpp)

target_link_libraries(LabyrinthGame PRIVATE labyrinth-engine labyrinth-content)