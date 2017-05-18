#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <basic/token.h>

class Parser {
public:
    using TokenizedString = std::vector<Token>;
    static std::unordered_map<std::string, Token::Type> tokens_mapping;
    static std::unordered_map<std::string, Token::Type> operations_mapping;

    Parser();

    TokenizedString Parse(const std::string &input);

private:
    TokenizedString ParseMap(const TokenizedString &input);
    TokenizedString ParseReduce(const TokenizedString &input);
    TokenizedString ParseDesc(const TokenizedString &input);

    TokenizedString Tokenize(const std::string &input);
    std::string WrapOperations(const std::string &input);
    Token ExtractToken(const std::string &word);
    Token ExtractOperation(const std::string &word);

    static std::unordered_set<char> to_wrap_;
};
