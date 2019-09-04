//
// Created by taojianping on 2019/8/19.
//

#ifndef JLOX_TOKEN_H
#define JLOX_TOKEN_H

#include "Enum.h"
#include <iostream>
using namespace std;

template<typename T>
class Token {
public:
    Token(TokenType t, string lexeme, T ll, int l) {
        type = t;
        lexeme = lexeme;
        literal = ll;
        line = l;
    }

    ~Token() {
        std::cout << "Îö¹¹ÖÐ~~~\n";
    }

    string toString();

private:
    TokenType type;
    string lexeme;
    // todo
    T literal;
    int line;
};

template<typename T>
string Token<T>::toString() {
    auto a = type;
    auto b = lexeme;
    auto c = literal;
    return std::__cxx11::string();
}


#endif //JLOX_TOKEN_H
