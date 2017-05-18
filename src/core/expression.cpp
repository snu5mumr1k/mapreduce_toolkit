#include <core/expression.h>

Expression::Expression(const std::vector<Token> &expression):
    expression_()
{}

Row Expression::Execute(const Row &input) const {
    return input;
}
