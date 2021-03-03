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
