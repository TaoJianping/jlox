//
// Created by taojianping on 2019/9/7.
//

#ifndef JLOX_EXPR_H
#define JLOX_EXPR_H


#include <any>
#include <utility>
#include <vector>
#include "Token.h"
//#include "AstPrinter.h"


// expression   → literal
//              | unary
//              | binary
//              | grouping ;
//
// literal    → NUMBER | STRING | "false" | "true" | "nil" ;
// grouping   → "(" expression ")" ;
// unary      → ( "-" | "!" ) expression ;
// binary     → expression operator expression ;
// operator   → "==" | "!=" | "<" | "<=" | ">" | ">="
//               | "+"  | "-"  | "*" | "/" ;


class Expr {

};


class Binary : public Expr {
public:
    Binary(Expr* l, const Token &o, Expr* r) : left(l), m_operator(o), right(r) {};
private:
    Expr* left;
    Token m_operator;
    Expr* right;
};


class Assign : Expr {
private:
    Token name;
    Expr* value;
public:
    Assign(const Token &n, Expr* v) : name(n), value(v) {};
};


class Call : Expr {
private:
    Token paren;
    Expr* callee;
    std::vector<Token*> arguments;
public:
    Call(const Token &p, Expr* c, std::vector<Token*> args) : paren(p), callee(c),
                                                                                arguments(std::move(args)) {};
};


class Get : Expr {
private:
    Token name;
    Expr* object;
public:
    Get(Expr* o, const Token &n) : object(o), name(n) {};
};


class Set : Expr {
private:
    Expr* object;
    Token name;
    Expr* value;
public:
    Set(Expr* o, const Token &n, Expr* v) : object(o), name(n), value(v) {};
};


class Grouping : Expr {
private:
    Expr* expression;
public:
    explicit Grouping(Expr* e) : expression(e) {};
};


class Literal : Expr {
private:
    Token value;
public:
    explicit Literal(const Token& v) : value(v) {};
};


class Logical : Expr {
public:
    Logical(Expr* l, const Token &o, Expr* r) : left(l), m_operator(o), right(r) {};
private:
    Expr* left;
    Token m_operator;
    Expr* right;
};


class Super : Expr {
private:
    Token keyword;
    Token method;
public:
    Super(const Token &k, const Token &m) : keyword(k), method(m) {};
};


class This : Expr {
private:
    Token keyword;
public:
    explicit This(const Token &k) : keyword(k) {};
};


class Unary : Expr {
private:
    Token m_operator;
    Expr* right;
public:
    Unary(const Token &o, Expr* r) : m_operator(o), right(r) {};
};


class Variable : Expr {
private:
    Token name;
public:
    explicit Variable(const Token &n) : name(n) {};
};




#endif //JLOX_EXPR_H
