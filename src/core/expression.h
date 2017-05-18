#pragma once

#include <vector>
#include <basic/token.h>
#include <table/row.h>

class Expression {
public:
    Expression() = default;
    Expression(const std::vector<Token> &expression);

    Row Execute(const Row &input) const;
private:
    std::vector<Token> expression_;
};
