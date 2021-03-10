//
// Created by tao on 2021/3/3.
//

#include "Stmt.h"

Block::Block(vector<Stmt*> statements) : statements(statements)
{

}

void Block::accept(StmtVisitor<void>* visitor)
{
	visitor->visit(this);
}

Expression::Expression(Expr* expression) : expression(expression)
{

}

void Expression::accept(StmtVisitor<void>* visitor)
{
	visitor->visit(this);
}

Print::Print(Expr* expression) : expression(expression)
{

}

void Print::accept(StmtVisitor<void>* visitor)
{
	visitor->visit(this);
}

Var::Var(Token* name, Expr* initializer) : name(name), initializer(initializer)
{

}

void Var::accept(StmtVisitor<void>* visitor)
{
	visitor->visit(this);
}

If::If(Expr* condition, Stmt* thenB, Stmt* elseB): condition(condition), thenBranch(thenB), elseBranch(elseB)
{

}

void If::accept(StmtVisitor<void>* visitor)
{
	visitor->visit(this);
}

While::While(Expr* condition, Stmt* body): condition(condition), body(body)
{

}

void While::accept(StmtVisitor<void>* visitor)
{
	visitor->visit(this);
}
