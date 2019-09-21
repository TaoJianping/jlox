//
// Created by taojianping on 2019/9/11.
//

#include "Parser.h"

Expr Parser::expression() {
    return equality();
}

Expr Parser::equality() {
    return Expr();
}
