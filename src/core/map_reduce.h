#pragma once

#include <string>
#include <core/parser.h>

class MapReduce {
public:
    MapReduce();

    bool Execute(const std::string &command);
    void RunDesc(const Parser::TokenizedString &expression);
    void RunReduce(const Parser::TokenizedString &expression);
    void RunMap(const Parser::TokenizedString &expression);
    void RunInterpreter();
};
