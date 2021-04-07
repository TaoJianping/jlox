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

If::If(Expr* condition, Stmt* thenB, Stmt* elseB) : condition(condition), thenBranch(thenB), elseBranch(elseB)
{

}

void If::accept(StmtVisitor<void>* visitor)
{
	visitor->visit(this);
}

While::While(Expr* condition, Stmt* body) : condition(condition), body(body)
{

}

void While::accept(StmtVisitor<void>* visitor)
{
	visitor->visit(this);
}

Function::Function(Token* name, vector<Token*> params, vector<Stmt*> body) : name(name), params(std::move(params)),
																			 body(std::move(body))
{

}

void Function::accept(StmtVisitor<void>* visitor)
{
	return visitor->visit(this);
}

Return::Return(Token* keyword, Expr* value) : keyword(keyword), value(value)
{

}

void Return::accept(StmtVisitor<void>* visitor)
{
	return visitor->visit(this);
}

Class::Class(Token* name, Variable* superclass, vector<Function*> methods): name(name), superclass(superclass),
																			methods(std::move(methods))
{

}

void Class::accept(StmtVisitor<void>* visitor)
{
	return visitor->visit(this);
}
