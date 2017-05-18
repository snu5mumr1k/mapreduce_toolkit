#include <sstream>
#include <core/parser.h>
#include <helpers/validators.h>

std::unordered_map<std::string, Token::Type> Parser::operations_mapping{
    {"map", Token::Type::MAP},
    {"reduce", Token::Type::REDUCE},
    {"desc", Token::Type::DESC},
    {"", Token::Type::CONTINUE},
    {"quit", Token::Type::QUIT},
    {"exit", Token::Type::QUIT},
};

std::unordered_map<std::string, Token::Type> Parser::tokens_mapping{
    {"insert", Token::Type::Insert},
    {"into", Token::Type::Into},
    {"select", Token::Type::Select},
    {"group", Token::Type::Group},
    {"by", Token::Type::By},
    {"from", Token::Type::From},
    {"where", Token::Type::Where},
    {"as", Token::Type::As},
    {"not", Token::Type::Not},
    {"and", Token::Type::And},
    {"or", Token::Type::Or},
    {"+", Token::Type::Plus},
    {"*", Token::Type::MultiplicationSign},
    {"/", Token::Type::DivisionSign},
    {"(", Token::Type::LeftBracket},
    {")", Token::Type::RightBracket},
    {"<", Token::Type::Less},
    {">", Token::Type::Greater},
    {"=", Token::Type::Equal},
    {"-", Token::Type::Minus},
    {",", Token::Type::ValuesDelimiter},
    {";", Token::Type::CommandDelimiter},
};

std::unordered_set<char> Parser::to_wrap_{
    '+',
    '*',
    '/',
    '(',
    ')',
    '<',
    '>',
    '=',
    '-',
    ',',
    ';'
};

Parser::Parser()
{}

Parser::TokenizedString Parser::Parse(const std::string &input) {
    TokenizedString expression = Tokenize(input);
    if (!expression.empty()) {
        switch (expression[0].type) {
            case Token::Type::MAP:
                return ParseMap(expression);
            case Token::Type::REDUCE:
                return ParseReduce(expression);
            case Token::Type::DESC:
                return ParseDesc(expression);
            default:
                break;
        }
    }
    return expression;
}

Parser::TokenizedString Parser::ParseMap(const Parser::TokenizedString &expression) {
    return expression;
}

Parser::TokenizedString Parser::ParseReduce(const Parser::TokenizedString &expression) {
    return expression;
}

Parser::TokenizedString Parser::ParseDesc(const Parser::TokenizedString &expression) {
    return expression;
}

Parser::TokenizedString Parser::Tokenize(const std::string &input) {
    std::stringstream ss{WrapOperations(input)};
    std::string word;
    TokenizedString result;
    ss >> word;
    result.push_back(ExtractOperation(word));
    while (ss >> word) {
        result.push_back(ExtractToken(word));
    }
    return result;
}

std::string Parser::WrapOperations(const std::string &input) {
    std::ostringstream os;
    for (char c : input) {
        if (to_wrap_.count(c) != 0) {
            os << ' ' << c << ' ';
        } else {
            os << c;
        }
    }
    return os.str();
}

Token Parser::ExtractOperation(const std::string &word) {
    Token new_token;
    if (operations_mapping.count(word) != 0) {
        new_token.type = operations_mapping[word];
    } else {
        throw std::runtime_error("Bad operation: \"" + word + "\"");
    }
    return new_token;
}

Token Parser::ExtractToken(const std::string &word) {
    Token new_token;
    if (tokens_mapping.count(word) != 0) {
        new_token.type = tokens_mapping[word];
    } else if (word == "true") {
        new_token.type = Token::Type::Value;
        new_token.value = Value(true);
    } else if (word == "false") {
        new_token.type = Token::Type::Value;
        new_token.value = Value(false);
    } else if (LooksLikeTableFilename(word)) {
        new_token.type = Token::Type::File;
        new_token.filename = word;
    } else if (LooksLikeColumn(word)) {
        new_token.type = Token::Type::Column;
        new_token.column_name = word;
    } else {
        new_token.type = Token::Type::Value;
        char *tmp = nullptr;
        int value = std::strtol(word.c_str(), &tmp, 10);
        if (*tmp == '.') {
            new_token.value = Value(std::strtod(word.c_str(), &tmp));
        } else {
            new_token.value = Value(value);
        }
        if (*tmp != '\0') {
            throw std::runtime_error("Bad value: " + word);
        }
    }
    return new_token;
}
