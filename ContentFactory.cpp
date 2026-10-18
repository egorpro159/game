#include "ContentFactory.h"
#include "Assets.h"
#include "Puzzles.h"

std::vector<Location> createLabyrinthLocations() {
    std::vector<Location> locations;
    locations.emplace_back(0, "Вход в лабиринт", entranceArt, std::vector<int>{1, 2}, true, nullptr);
    locations.emplace_back(1, "Тёмный коридор", corridorArt, std::vector<int>{0, 3}, false, puzzleRiddle);
    locations.emplace_back(2, "Зал загадок", hallArt, std::vector<int>{0, 3}, false, puzzleMath);
    locations.emplace_back(3, "Выход из лабиринта", exitArt, std::vector<int>{}, false, puzzleChoice);
    return locations;
}