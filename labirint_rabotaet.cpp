#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <cctype>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// -------------------------------------------------------------------
//  Класс локации
// -------------------------------------------------------------------
class Location {
public:
    int id;
    std::string name;
    std::vector<std::string> asciiArt;
    std::vector<int> connections;
    bool isOpen;
    std::function<bool()> puzzle;

    Location(int id,
        const std::string& name,
        const std::vector<std::string>& art,
        const std::vector<int>& conn,
        bool open,
        std::function<bool()> pzl)
        : id(id),
        name(name),
        asciiArt(art),
        connections(conn),
        isOpen(open),
        puzzle(pzl) {
    }
};

// -------------------------------------------------------------------
//  Функция очистки строки
// -------------------------------------------------------------------
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");

    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}

// -------------------------------------------------------------------
//  Головоломка 1
// -------------------------------------------------------------------
bool puzzleRiddle() {
    std::cout << "\n=== Головоломка ===\n";
    std::cout << "Загадка: 'Не лает, не кусает, а в дом не пускает.'\n";
    std::cout << "Что это?\n";
    std::cout << "Твой ответ: ";

    std::string ans;
    std::getline(std::cin, ans);

    ans = trim(ans);

    if (ans == "замок" || ans == "Замок") {
        std::cout << "✅ Правильно! Дверь открыта.\n";
        return true;
    }
    else {
        std::cout << "❌ Неправильно.\n";
        return false;
    }
}

// -------------------------------------------------------------------
//  Головоломка 2
// -------------------------------------------------------------------
bool puzzleMath() {
    std::cout << "\n=== Головоломка ===\n";
    std::cout << "Реши пример: 12 * 8 - 15 = ?\n";
    std::cout << "Твой ответ: ";

    int answer;

    if (!(std::cin >> answer)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "❌ Нужно ввести число.\n";
        return false;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (answer == 81) {
        std::cout << "✅ Верно!\n";
        return true;
    }
    else {
        std::cout << "❌ Неправильно.\n";
        return false;
    }
}

// -------------------------------------------------------------------
//  Финальная головоломка
// -------------------------------------------------------------------
bool puzzleChoice() {
    std::cout << "\n=== Финальная дверь ===\n";
    std::cout << "Выбери правильный пароль:\n";
    std::cout << "1. Свобода\n";
    std::cout << "2. Выход\n";
    std::cout << "3. Победа\n";
    std::cout << "Номер: ";

    std::string choice;
    std::getline(std::cin, choice);

    if (choice == "2") {
        std::cout << "✅ Пароль верный!\n";
        return true;
    }
    else {
        std::cout << "❌ Неверный пароль.\n";
        return false;
    }
}

// -------------------------------------------------------------------
//  ASCII ART
// -------------------------------------------------------------------
std::vector<std::string> entranceArt = {
    "   _______   ",
    "  /           \\  ",
    " |   ВХОД     |  ",
    " |    В       |  ",
    " |  ЛАБИРИНТ  |  ",
    "  \\___________/  ",
    "      |   |      ",
    "      |   |      "
};

std::vector<std::string> corridorArt = {
    "  *********  ",
    "  *           *  ",
    "  *   ТЁМНЫЙ  *  ",
    "  *  КОРИДОР  *  ",
    "  *     ?     *  ",
    "  *********  "
};

std::vector<std::string> hallArt = {
    "    +-------+    ","   /         \\   ",
    "  |   ЗАЛ    |   ",
    "  | ЗАГАДОК  |   ",
    "   \\_________/   "
};

std::vector<std::string> exitArt = {
    "    /////////     ",
    "   /// ВЫХОД \\\\\\   ",
    "  //// ИЗ    \\\\\\  ",
    " //// ЛАБИРИНТА \\\\\\ ",
    "   \\\\\\_______////   "
};

// -------------------------------------------------------------------
//  Очистка экрана
// -------------------------------------------------------------------
void clearScreen() {
    std::system(CLEAR_SCREEN);
}

// -------------------------------------------------------------------
//  Показ локации
// -------------------------------------------------------------------
void showLocation(const Location& loc) {
    std::cout << "\n=== " << loc.name
        << " (ID: " << loc.id << ") ===\n\n";

    for (const auto& line : loc.asciiArt) {
        std::cout << line << '\n';
    }

    std::cout << '\n';
}

// -------------------------------------------------------------------
//  Показ доступных переходов
// -------------------------------------------------------------------
void showConnections(const Location& cur,
    const std::vector<Location>& locs) {

    std::cout << "Куда можно пойти:\n";

    for (int nxt : cur.connections) {
        const Location& target = locs[nxt];

        std::string state =
            target.isOpen
            ? "открыто"
            : "закрыто";

        std::cout << "  "
            << nxt
            << " -> "
            << target.name
            << " ["
            << state
            << "]\n";
    }

    std::cout << "  quit -> выйти из игры\n";
}

// -------------------------------------------------------------------
//  MAIN
// -------------------------------------------------------------------
int main() {

#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    std::vector<Location> locations;

    locations.emplace_back(
        0,
        "Вход в лабиринт",
        entranceArt,
        std::vector<int>{1, 2},
        true,
        nullptr
    );

    locations.emplace_back(
        1,
        "Тёмный коридор",
        corridorArt,
        std::vector<int>{0, 3},
        false,
        puzzleRiddle
    );

    locations.emplace_back(
        2,
        "Зал загадок",
        hallArt,
        std::vector<int>{0, 3},
        false,
        puzzleMath
    );

    locations.emplace_back(
        3,
        "Выход из лабиринта",
        exitArt,
        std::vector<int>{},
        false,
        puzzleChoice
    );

    int currentId = 0;

    while (true) {

        clearScreen();

        Location& cur = locations[currentId];

        showLocation(cur);

        // Победа
        if (cur.id == 3) {
            std::cout << "🏆 ПОЗДРАВЛЯЕМ! ТЫ ВЫБРАЛСЯ ИЗ ЛАБИРИНТА! 🏆\n";
            break;
        }

        showConnections(cur, locations);

        std::cout << "\nКуда идём?\n";
        std::cout << "Введи ID или quit: ";

        std::string input;
        std::getline(std::cin, input);

        if (input == "quit") {
            std::cout << "\nИгра завершена.\n";
            break;
        }

        int targetId;

        try {
            targetId = std::stoi(input);
        }
        catch (...) {
            std::cout << "\n❌ Нужно ввести число.\n";

            std::cout << "Нажми Enter...";
            std::cin.get();

            continue;
        }

        // Проверка диапазона
        if (targetId < 0 || targetId >= (int)locations.size()) {

            std::cout << "\n❌ Такой локации не существует.\n";

            std::cout << "Нажми Enter...";
            std::cin.get();

            continue;
        }

        // Проверка соединения
        auto it = std::find(
            cur.connections.begin(),
            cur.connections.end(),
            targetId
        );

        if (it == cur.connections.end()) {

            std::cout << "\n❌ Туда нельзя попасть отсюда.\n";

            std::cout << "Нажми Enter...";
            std::cin.get();

            continue;
        }Location& target = locations[targetId];

        // Если уже открыта
        if (target.isOpen) {
            currentId = targetId;
            continue;
        }

        // Если есть головоломка
        if (target.puzzle) {

            bool solved = target.puzzle();

            if (solved) {
                target.isOpen = true;
                target.puzzle = nullptr;
                currentId = targetId;
            }
            else {
                std::cout << "\nДверь осталась закрытой.\n";

                std::cout << "Нажми Enter...";
                std::cin.get();
            }
        }
        else {

            std::cout << "\n❌ Ошибка: дверь закрыта без головоломки.\n";

            std::cout << "Нажми Enter...";
            std::cin.get();
        }
    }

    std::cout << "\nСпасибо за игру!\n";

    return 0;
}