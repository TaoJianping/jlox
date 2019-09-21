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





class Expr {

};

template<typename T>
class Binary : Expr {
public:
    Binary(Expr l, const Token<T> &o, Expr r) : left(l), m_operator(o), right(r) {};
private:
    Expr left;
    Token<T> m_operator;
    Expr right;
};


template<typename T>
class Assign : Expr {
private:
    Token<T> name;
    Expr value;
public:
    Assign(const Token<T> &n, Expr v) : name(n), value(v) {};
};


template<typename T>
class Call : Expr {
private:
    Token<T> paren;
    Expr callee;
    std::vector<Token<T>> arguments;
public:
    Call(const Token<T> &p, Expr c, std::vector<Token<T>> args) : paren(p), callee(c),
                                                                                arguments(std::move(args)) {};
};


template<typename T>
class Get : Expr {
private:
    Token<T> name;
    Expr object;
public:
    Get(Expr o, const Token<T> &n) : object(o), name(n) {};
};


template<typename T>
class Set : Expr {
private:
    Expr object;
    Token<T> name;
    Expr value;
public:
    Set(Expr o, const Token<T> &n, Expr v) : object(o), name(n), value(v) {};
};


template<typename T>
class Grouping : Expr {
private:
    Expr expression;
public:
    explicit Grouping(Expr e) : expression(e) {};
};


template<typename T>
class Literal : Expr {
private:
    T value;
public:
    explicit Literal(T v) : value(v) {};
};


template<typename T>
class Logical : Expr {
public:
    Logical(Expr l, const Token<T> &o, Expr r) : left(l), m_operator(o), right(r) {};
private:
    Expr left;
    Token<T> m_operator;
    Expr right;
};


template<typename T>
class Super : Expr {
private:
    Token<T> keyword;
    Token<T> method;
public:
    Super(const Token<T> &k, const Token<T> &m) : keyword(k), method(m) {};
};


template<typename T>
class This : Expr {
private:
    Token<T> keyword;
public:
    explicit This(const Token<T> &k) : keyword(k) {};
};


template<typename T>
class Unary : Expr {
private:
    Token<T> m_operator;
    Expr right;
public:
    Unary(const Token<T> &o, Expr r) : m_operator(o), right(r) {};
};


template<typename T>
class Variable : Expr {
private:
    Token<T> name;
public:
    explicit Variable(const Token<T> &n) : name(n) {};
};




#endif //JLOX_EXPR_H
