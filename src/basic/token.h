#pragma once

#include <string>
#include <basic/value.h>

struct Token {
    enum class Type {
        Insert,
        Into,
        Select,
        From,
        Where,
        Group,
        By,
        As,
        Plus,
        Minus,
        MultiplicationSign,
        DivisionSign,
        LeftBracket,
        RightBracket,
        Less,
        Greater,
        Equal,
        Not,
        And,
        Or,
        Value,
        Column,
        ValuesDelimiter,
        CommandDelimiter,
        File,
        MAP,
        REDUCE,
        DESC,
        CONTINUE,
        QUIT,
        INSERT_INTO,
        SELECT,
        FROM,
        WHERE,
    };

    Type type;
    Value value;
    std::string column_name;
    std::string filename;
};
