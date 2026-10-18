#include "Location.h"

Location::Location(int id, const std::string& name, const std::vector<std::string>& art,
                   const std::vector<int>& conn, bool open, std::function<bool()> pzl)
    : id(id), name(name), asciiArt(art), connections(conn), isOpen(open), puzzle(pzl) {
}