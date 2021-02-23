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


class Binary;
class Grouping;
class Literal;
class Unary;
class Ternary;
class Assign;
class Call;
class Get;
class Set;
class Logical;
class Super;
class This;
class Variable;

template <typename T>
class Visitor {
	T visitBinaryExpr(Binary expr) = 0;
	T visitGroupingExpr(Grouping expr) = 0;
	T visitLiteralExpr(Literal expr) = 0;
	T visitTernaryExpr(Ternary expr) = 0;
	T visitUnaryExpr(Unary expr) = 0;
};


class Expr {
//	void accept(Visitor visitor);

};


class Binary : public Expr {
public:
	Binary(Expr* l, const Lexeme::Token &o, Expr* r) : left(l), m_operator(o), right(r) {};
private:
	Expr* left;
	Lexeme::Token m_operator;
	Expr* right;
};


class Grouping : public Expr {
private:
	Expr* expression;
public:
	explicit Grouping(Expr* e) : expression(e) {};
};


class Literal : public Expr {
private:
	Lexeme::Token value;
public:
	explicit Literal(const Lexeme::Token& v) : value(v) {};
};


class Unary : public Expr {
private:
	Lexeme::Token m_operator;
	Expr* right;
public:
	Unary(const Lexeme::Token &o, Expr* r) : m_operator(o), right(r) {};
};


class Ternary : public Expr {
private:
	Lexeme::Token m_operator;
	Expr left;
	Expr middle;
	Expr right;
public:
	Ternary(Lexeme::Token m_operator, Expr left, Expr middle, Expr right) : m_operator(m_operator), right(right) {};

};



//class Assign : Expr {
//private:
//	Lexeme::Token name;
//	Expr* value;
//public:
//	Assign(const Lexeme::Token &n, Expr* v) : name(n), value(v) {};
//};
//
//
//class Call : Expr {
//private:
//	Lexeme::Token paren;
//	Expr* callee;
//	std::vector<Lexeme::Token*> arguments;
//public:
//	Call(const Lexeme::Token &p, Expr* c, std::vector<Lexeme::Token*> args) : paren(p), callee(c),
//																			  arguments(std::move(args)) {};
//};
//
//
//class Get : Expr {
//private:
//	Lexeme::Token name;
//	Expr* object;
//public:
//	Get(Expr* o, const Lexeme::Token &n) : object(o), name(n) {};
//};
//
//
//class Set : Expr {
//private:
//	Expr* object;
//	Lexeme::Token name;
//	Expr* value;
//public:
//	Set(Expr* o, const Lexeme::Token &n, Expr* v) : object(o), name(n), value(v) {};
//};


//class Logical : Expr {
//public:
//	Logical(Expr* l, const Lexeme::Token &o, Expr* r) : left(l), m_operator(o), right(r) {};
//private:
//	Expr* left;
//	Lexeme::Token m_operator;
//	Expr* right;
//};
//
//
//class Super : Expr {
//private:
//	Lexeme::Token keyword;
//	Lexeme::Token method;
//public:
//	Super(const Lexeme::Token &k, const Lexeme::Token &m) : keyword(k), method(m) {};
//};
//
//
//class This : Expr {
//private:
//	Lexeme::Token keyword;
//public:
//	explicit This(const Lexeme::Token &k) : keyword(k) {};
//};
//
//
//class Variable : Expr {
//private:
//	Lexeme::Token name;
//public:
//	explicit Variable(const Lexeme::Token &n) : name(n) {};
//};

//	template<typename T>
//	T accept(Visitor)





#endif //JLOX_EXPR_H
