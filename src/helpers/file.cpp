#include <fstream>
#include <sstream>
#include <helpers/file.h>
#include <params.h>
#include <helpers/singleton.h>

std::vector<std::string> GetDescription(const std::string &filename) {
    std::string tables = Singleton<Params>()->Get("tables_dir");
    std::fstream table{tables + filename, table.in};
    if (!table.is_open()) {
        throw std::runtime_error("Failed to open file: data/" + filename);
    }
    std::string header;
    std::getline(table, header);
    return Split(header);
}

std::vector<std::string> Split(const std::string &line) {
    std::string sep = Singleton<Params>()->Get("sep");
    std::vector<std::string> result;
    char *token = std::strtok(const_cast<char *>(line.c_str()), sep.c_str());
    while (token != nullptr) {
        result.push_back(std::string(token));
        token = std::strtok(nullptr, sep.c_str());
    }
    return result;
}
