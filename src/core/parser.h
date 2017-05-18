#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <basic/token.h>
#include <core/ops_description.h>
#include <core/expression.h>

class Parser {
public:
    static std::unordered_map<std::string, Token::Type> tokens_mapping;
    static std::unordered_map<std::string, Token::Type> operations_mapping;

    OperationDescription Parse(const std::string &input);

private:
    using TokenizedString = std::vector<Token>;

    OperationDescription ParseMap();
    OperationDescription ParseReduce();
    OperationDescription ParseDesc();

    std::string ParseInsert();
    Expression ParseSelect();
    std::string ParseFrom();
    Expression ParseWhere();

    TokenizedString Tokenize(const std::string &input);
    std::string WrapOperations(const std::string &input);
    Token ExtractToken(const std::string &word);
    Token ExtractOperation(const std::string &word);

    bool InExpression(Token::Type type);

    static std::unordered_set<char> to_wrap_;

    struct State {
        TokenizedString::iterator curr;
        TokenizedString::iterator end;
    };

    State state_;
};
