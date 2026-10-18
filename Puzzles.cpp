#include "Puzzles.h"
#include <iostream>
#include <limits>

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    return str.substr(start, end - start + 1);
}

bool puzzleRiddle() {
    std::cout << "\n=== Головоломка ===\n";
    std::cout << "Загадка: 'Не лает, не кусает, а в дом не пускает.'\nЧто это?\nТвой ответ: ";
    std::string ans;
    std::getline(std::cin, ans);
    ans = trim(ans);
    if (ans == "замок" || ans == "Замок") {
        std::cout << "✅ Правильно! Дверь открыта.\n";
        return true;
    }
    std::cout << "❌ Неправильно.\n";
    return false;
}

bool puzzleMath() {
    std::cout << "\n=== Головоломка ===\n";
    std::cout << "Реши пример: 12 * 8 - 15 = ?\nТвой ответ: ";
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
    std::cout << "❌ Неправильно.\n";
    return false;
}

bool puzzleChoice() {
    std::cout << "\n=== Финальная дверь ===\n";
    std::cout << "Выбери правильный пароль:\n1. Свобода\n2. Выход\n3. Победа\nНомер: ";
    std::string choice;
    std::getline(std::cin, choice);
    if (choice == "2") {
        std::cout << "✅ Пароль верный!\n";
        return true;
    }
    std::cout << "❌ Неверный пароль.\n";
    return false;
}