#include <iostream>
#include <string>
#include <core/map_reduce.h>

MapReduce::MapReduce()
{}

void MapReduce::RunInterpreter() {
    std::cout << "MapReduce toolkit utility by <Andrey Feofilaktov andarpolis@gmail.com>" << std::endl;
    std::cout << "for help use <help> command" << std::endl;
    while (true) {
        std::cout << ":) ";
        std::string command;
        std::getline(std::cin, command);
        if (command == "quit;") {
            break;
        }
        std::cout << command << std::endl;
    }
}
