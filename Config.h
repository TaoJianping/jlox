//
// Created by taojianping on 2019/9/4.
//

#ifndef JLOX_CONFIG_H
#define JLOX_CONFIG_H

#include <string>
#include <unordered_map>
#include "Src/Common/Enum.h"

const std::unordered_map<std::string, TokenType> KEYWORDS = {
        {"and",    TokenType::AND},
        {"class",  TokenType::CLASS},
        {"else",   TokenType::ELSE},
        {"false",  TokenType::FALSE},
        {"for",    TokenType::FOR},
        {"fun",    TokenType::FUN},
        {"if",     TokenType::IF},
        {"nil",    TokenType::NIL},
        {"or",     TokenType::OR},
        {"print",  TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super",  TokenType::SUPER},
        {"this",   TokenType::THIS},
        {"true",   TokenType::TRUE},
        {"var",    TokenType::VAR},
        {"while",  TokenType::WHILE},
};

#endif //JLOX_CONFIG_H
