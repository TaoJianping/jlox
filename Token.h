//
// Created by taojianping on 2019/8/19.
//

#ifndef JLOX_TOKEN_H
#define JLOX_TOKEN_H

#include "Enum.h"
#include <iostream>
#include <utility>
using namespace std;

class Token {
public:
    TokenType type;
    Token(TokenType t, string lexeme, std::string ll, int l) {
        type = t;
        lexeme = lexeme;
        literal = std::move(ll);
        line = l;
    }

    ~Token() {
        std::cout << "������~~~\n";
    }

    string toString();

private:
    string lexeme;
    // todo
    std::string literal;
    int line;
};


#endif //JLOX_TOKEN_H
