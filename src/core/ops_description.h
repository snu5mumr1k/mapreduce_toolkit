#pragma once

#include <string>
#include <vector>
#include <basic/token.h>
#include <core/expression.h>

enum class OperationType {
    Map,
    Reduce,
    Desc,
    Quit,
    Continue,
};

struct OperationDescription {
    OperationType type;

    std::string insert_into;
    std::string from;
    Expression select;
    Expression where;

    std::vector<std::string> columns_order;
    std::vector<Token> tokens;
};
