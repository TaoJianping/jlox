//
// Created by taojianping on 2019/9/7.
//

#include "Expr.h"

#include <utility>

std::string Literal::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

LoxType Literal::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

void Literal::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}

std::string Unary::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

LoxType Unary::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

void Unary::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}

std::string Grouping::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

LoxType Grouping::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

void Grouping::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}

std::string Binary::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

LoxType Binary::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

void Binary::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}

Variable::Variable(Token* token) : name(token)
{

}

std::string Variable::accept(Visitor<std::string>* visitor)
{
	return std::string();
}

LoxType Variable::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

void Variable::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}

//std::string Variable::accept(Visitor<std::string>* visitor)
//{
//	return visitor->visit(this);
//}
Assign::Assign(Token* name, Expr* value) : name(name), value(value)
{

}

LoxType Assign::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

std::string Assign::accept(Visitor<std::string>* visitor)
{
	return std::string();
}

void Assign::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}

Logical::Logical(Expr* left, Token* _operator, Expr* right) : left(left), _operator(_operator), right(right)
{

}

std::string Logical::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

LoxType Logical::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

void Logical::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}

Call::Call(Expr* callee, Token* paren, vector<Expr*> arguments) : callee(callee), paren(paren),
																  arguments(std::move(arguments))
{

}

LoxType Call::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

std::string Call::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

void Call::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}

Get::Get(Expr* object, Token* name) : object(object), name(name)
{

}

std::string Get::accept(Visitor<std::string>* visitor)
{
	return std::__cxx11::string();
}

LoxType Get::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

void Get::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}

Set::Set(Expr* object, Token* name, Expr* value) : object(object), name(name), value(value)
{

}

std::string Set::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

LoxType Set::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

void Set::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}

This::This(Token* keyword): keyword(keyword)
{

}

std::string This::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

LoxType This::accept(Visitor<LoxType>* visitor)
{
	return visitor->visit(this);
}

void This::accept(Visitor<void>* visitor)
{
	return visitor->visit(this);
}
