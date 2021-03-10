//
// Created by tao on 2021/3/3.
//

#ifndef JLOXTESTS_STMT_H
#define JLOXTESTS_STMT_H

#include <variant>
#include <string>
#include <vector>

#include "Expr.h"

using std::variant;
using std::vector;
using Lexeme::Token;

class Block;

class Expression;

class Print;

class Var;

class If;

class While;

template<typename T>
class StmtVisitor
{
public:
	virtual T visit(const Block* expr) = 0;

	virtual T visit(const Expression* expr) = 0;

	virtual T visit(const Print* expr) = 0;

	virtual T visit(const Var* expr) = 0;

	virtual T visit(const If* expr) = 0;

	virtual T visit(const While* expr) = 0;
};


class Stmt
{
public:
	virtual void accept(StmtVisitor<void>* visitor) = 0;
};


class Block : public Stmt
{
public:
	vector<Stmt*> statements;

	explicit Block(vector<Stmt*> statements);

	void accept(StmtVisitor<void>* visitor) override;
};


class Expression : public Stmt
{
public:
	Expr* expression;

	explicit Expression(Expr* expression);

	void accept(StmtVisitor<void>* visitor) override;
};


class Print : public Stmt
{
public:
	Expr* expression;

	explicit Print(Expr* expression);

	void accept(StmtVisitor<void>* visitor) override;
};


class Var : public Stmt
{
public:
	Token* name;
	Expr* initializer;

	Var(Token* name, Expr* initializer);

	void accept(StmtVisitor<void>* visitor) override;
};


class If : public Stmt
{
public:
	Expr* condition;
	Stmt* thenBranch;
	Stmt* elseBranch;

	If(Expr* condition, Stmt* thenB, Stmt* elseB);
	void accept(StmtVisitor<void>* visitor) override;
};


class While : public Stmt
{
public:
	Expr* condition;
	Stmt* body;

	While(Expr* condition, Stmt* body);
	void accept(StmtVisitor<void>* visitor) override;
};

#endif //JLOXTESTS_STMT_H
