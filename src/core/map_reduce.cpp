#include <iostream>
#include <core/map_reduce.h>

MapReduce::MapReduce()
{}

void MapReduce::RunInterpreter() {
    std::cout << "MapReduce toolkit utility by Andrey Feofilaktov<andarpolis@gmail.com>" << std::endl;
    std::string command;
    do {
        std::cout << ":) ";
        std::getline(std::cin, command);
    } while(Execute(command) && !std::cin.eof());
    std::cout << std::endl;
}

bool MapReduce::Execute(const std::string &command) {
    Parser p;
    Parser::TokenizedString expression;
    try {
        expression = p.Parse(command);
    } catch (const std::runtime_error &re) {
        std::cout << re.what() << std::endl;
        return true;
    }
    switch (expression[0].type) {
        case Token::Type::MAP:
            RunMap(expression);
            break;
        case Token::Type::REDUCE:
            RunReduce(expression);
            break;
        case Token::Type::DESC:
            RunDesc(expression);
            break;
        case Token::Type::CONTINUE:
            break;
        case Token::Type::QUIT:
            return false;
        default:
            std::cout << "Failed to parse command, try again" << std::endl;
    }
    return true;
}

void MapReduce::RunDesc(const Parser::TokenizedString &expression) {
}

void MapReduce::RunReduce(const Parser::TokenizedString &expression) {
}

void MapReduce::RunMap(const Parser::TokenizedString &expression) {
}
