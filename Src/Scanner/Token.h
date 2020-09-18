//
// Created by taojianping on 2019/8/19.
//

#ifndef JLOX_TOKEN_H
#define JLOX_TOKEN_H

#include "../Common/Enum.h"
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
        std::cout << "Fuck~~~\n";
    }

    friend ostream &operator<<( ostream &output, const Token &token )
    {
        string typeStr;
        switch (token.type) {
            case TokenType::LEFT_PAREN:
                typeStr = "LEFT_PAREN";
                break;
            default:
                break;
        }

//        output << "TokenType : " << token.lexeme;
        output << "TokenLexeme : " << token.lexeme;
        return output;
    }

    string toString();
    int line;
    string lexeme;
    std::string literal;

private:
    // todo
};


#endif //JLOX_TOKEN_H
