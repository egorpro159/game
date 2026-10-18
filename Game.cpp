#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <limits>

void showLocation(const Location& loc) {
    std::cout << "\n=== " << loc.name << " (ID: " << loc.id << ") ===\n\n";
    for (const auto& line : loc.asciiArt) {
        std::cout << line << '\n';
    }
    std::cout << '\n';
}

void showConnections(const Location& cur, const std::vector<Location>& locs) {
    std::cout << "Куда можно пойти:\n";
    for (int nxt : cur.connections) {
        const Location& target = locs[nxt];
        std::string state = target.isOpen ? "открыто" : "закрыто";
        std::cout << "  " << nxt << " -> " << target.name << " [" << state << "]\n";
    }
    std::cout << "  quit -> выйти из игры\n";
}

void Game::run(std::vector<Location>& locations) {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    int currentId = 0;

    while (true) {
        clearScreen();
        Location& cur = locations[currentId];
        showLocation(cur);

        if (cur.id == 3) {
            std::cout << "🏆 ПОЗДРАВЛЯЕМ! ТЫ ВЫБРАЛСЯ ИЗ ЛАБИРИНТА! 🏆\n";
            break;
        }

        showConnections(cur, locations);
        std::cout << "\nКуда идём?\nВведи ID или quit: ";

        std::string input;
        std::getline(std::cin, input);

        if (input == "quit") {
            std::cout << "\nИгра завершена.\n";
            break;
        }

        int targetId;
        try {
            targetId = std::stoi(input);
        } catch (...) {
            std::cout << "\n❌ Нужно ввести число.\nНажми Enter...";
            std::cin.get();
            continue;
        }

        if (targetId < 0 || targetId >= (int)locations.size()) {
            std::cout << "\n❌ Такой локации не существует.\nНажми Enter...";
            std::cin.get();
            continue;
        }

        auto it = std::find(cur.connections.begin(), cur.connections.end(), targetId);
        if (it == cur.connections.end()) {
            std::cout << "\n❌ Туда нельзя попасть отсюда.\nНажми Enter...";
            std::cin.get();
            continue;
        }

        Location& target = locations[targetId];
        if (target.isOpen) {
            currentId = targetId;
            continue;
        }

        if (target.puzzle) {
            bool solved = target.puzzle();
            if (solved) {
                target.isOpen = true;
                target.puzzle = nullptr;
                currentId = targetId;
            } else {
                std::cout << "\nДверь осталась закрытой.\nНажми Enter...";
                std::cin.get();
            }
        } else {
            std::cout << "\n❌ Ошибка: дверь закрыта без головоломки.\nНажми Enter...";
            std::cin.get();
        }
    }

    std::cout << "\nСпасибо за игру!\n";
}