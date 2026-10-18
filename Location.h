#pragma once
#include <string>
#include <vector>
#include <functional>

class Location {
public:
    int id;
    std::string name;
    std::vector<std::string> asciiArt;
    std::vector<int> connections;
    bool isOpen;
    std::function<bool()> puzzle;

    Location(int id, const std::string& name, const std::vector<std::string>& art,
             const std::vector<int>& conn, bool open, std::function<bool()> pzl);
};