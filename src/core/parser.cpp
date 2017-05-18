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

OperationDescription Parser::Parse(const std::string &input) {
    TokenizedString expression = Tokenize(input);
    if (!expression.empty()) {
        state_.curr = expression.begin();
        state_.end = expression.end();
        switch (state_.curr++->type) {
            case Token::Type::MAP:
                return ParseMap();
            case Token::Type::REDUCE:
                return ParseReduce();
            case Token::Type::DESC:
                return ParseDesc();
            default:
                break;
        }
    }
    OperationDescription op_desc;
    op_desc.type = OperationType::Continue;
    return op_desc;
}

OperationDescription Parser::ParseMap() {
    OperationDescription op_desc;
    op_desc.type = OperationType::Map;
    op_desc.insert_into = ParseInsert();
    op_desc.select = ParseSelect();
    op_desc.from = ParseFrom();
    op_desc.where = ParseWhere();
    return op_desc;
}

std::string Parser::ParseInsert() {
    if (state_.curr == state_.end || state_.curr->type != Token::Type::Insert) {
        throw std::runtime_error("Bad syntax near 'insert'");
    }
    state_.curr++;
    if (state_.curr == state_.end || state_.curr->type != Token::Type::Into) {
        throw std::runtime_error("Bad syntax near 'insert'");
    }
    state_.curr++;
    if (state_.curr == state_.end || state_.curr->type != Token::Type::File) {
        throw std::runtime_error("Not a filename after 'insert into'");
    }
    std::string result = state_.curr->filename;
    state_.curr++;
    return result;
}

Expression Parser::ParseSelect() {
    if (state_.curr == state_.end || state_.curr->type != Token::Type::Select) {
        throw std::runtime_error("Bad syntax near 'select'");
    }
    state_.curr++;
    auto start_sequence = state_.curr;
    while (state_.curr != state_.end && InExpression(state_.curr->type)) {
        state_.curr++;
    }
    return Expression({start_sequence, state_.curr});
}

std::string Parser::ParseFrom() {
    if (state_.curr == state_.end || state_.curr->type != Token::Type::From) {
        throw std::runtime_error("Bad syntax near 'from'");
    }
    state_.curr++;
    if (state_.curr == state_.end || state_.curr->type != Token::Type::File) {
        throw std::runtime_error("Not a filename after 'from'");
    }
    std::string result = state_.curr->filename;
    state_.curr++;
    return result;
}

Expression Parser::ParseWhere() {
    if (state_.curr == state_.end || state_.curr->type != Token::Type::Where) {
        throw std::runtime_error("Bad syntax near 'where'");
    }
    state_.curr++;
    auto start_sequence = state_.curr;
    while (state_.curr != state_.end && InExpression(state_.curr->type)) {
        state_.curr++;
    }
    return Expression({start_sequence, state_.curr});
}

OperationDescription Parser::ParseReduce() {
    OperationDescription op_desc;
    op_desc.type = OperationType::Reduce;
    op_desc.insert_into = ParseInsert();
    op_desc.select = ParseSelect();
    op_desc.from = ParseFrom();
    op_desc.where = ParseWhere();
    return op_desc;
}

OperationDescription Parser::ParseDesc() {
    for (auto token = state_.curr; token != state_.end; ++token) {
        if (token->type != Token::Type::File) {
            throw std::runtime_error("Can't describe: not a table");
        }
    }
    OperationDescription op_desc;
    op_desc.type = OperationType::Desc;
    op_desc.tokens = {state_.curr, state_.end};
    return op_desc;
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
    } else if (LooksLikeTableFilename(word)) {
        new_token.type = Token::Type::File;
        new_token.filename = word;
    } else if (LooksLikeColumn(word)) {
        new_token.type = Token::Type::Column;
        new_token.column_name = word;
    } else {
        new_token.type = Token::Type::Value;
        new_token.value = Value::FromString(word);
    }
    return new_token;
}

bool Parser::InExpression(Token::Type type) {
    return (
        type == Token::Type::Value ||
        type == Token::Type::ValuesDelimiter ||
        type == Token::Type::As ||
        type == Token::Type::Plus ||
        type == Token::Type::Minus ||
        type == Token::Type::MultiplicationSign ||
        type == Token::Type::DivisionSign ||
        type == Token::Type::LeftBracket ||
        type == Token::Type::RightBracket ||
        type == Token::Type::Less ||
        type == Token::Type::Greater ||
        type == Token::Type::Equal ||
        type == Token::Type::Not ||
        type == Token::Type::And ||
        type == Token::Type::Or ||
        type == Token::Type::Value ||
        type == Token::Type::Column
    );
}
