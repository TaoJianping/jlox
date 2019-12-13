//
// Created by taojianping on 2019/9/11.
//

#ifndef JLOX_PARSER_H
#define JLOX_PARSER_H


#include <vector>
#include <any>
#include "Token.h"
#include "Expr.h"

using namespace std;

class ParseException : std::exception {
};


class Parser {
private:
    std::vector<Token *> tokens;
    int current;

    Expr *expression();

    Expr *equality();

    Expr *comparison();

    Expr *addition();

    Expr *multiplication();

    Expr *unary();

    Expr *primary();

    Token *consume(TokenType, const std::string &);

    ParseException *error(const Token &, const std::string &);

    bool match(const vector<TokenType> &);

    bool match(TokenType);

    bool check(TokenType type);

    Token *advance();

    bool isAtEnd();

    Token *peek();

    Token *previous();


public:
    Expr *parse();

    explicit Parser(const std::vector<Token *> &ts) {
        tokens = ts;
        current = 0;
    }
};


#endif //JLOX_PARSER_H
