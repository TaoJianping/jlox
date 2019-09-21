//
// Created by taojianping on 2019/9/11.
//

#ifndef JLOX_PARSER_H
#define JLOX_PARSER_H


#include <vector>
#include <any>
#include "Token.h"
#include "Expr.h"

class Parser {
private:
    std::vector<Token<std::any>> tokens;
    int current;
    Expr expression();
    Expr equality();

public:
    explicit Parser(const std::vector<Token<std::any>> & ts) {
        tokens = ts;
        current = 0;
    }
};


#endif //JLOX_PARSER_H
