#include "ContentFactory.h"
#include "Game.h"
#include <vector>

#ifdef _WIN32
#include <cstdlib>
#endif

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    std::vector<Location> locations = createLabyrinthLocations();
    Game engine;
    engine.run(locations);

    return 0;
}