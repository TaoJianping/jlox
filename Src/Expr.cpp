//
// Created by taojianping on 2019/9/7.
//

#include "Expr.h"

#include <utility>

std::string Literal::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

InterpreterValueType Literal::accept(Visitor<InterpreterValueType>* visitor)
{
	return visitor->visit(this);
}

std::string Unary::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

InterpreterValueType Unary::accept(Visitor<InterpreterValueType>* visitor)
{
	return visitor->visit(this);
}

std::string Grouping::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

InterpreterValueType Grouping::accept(Visitor<InterpreterValueType>* visitor)
{
	return visitor->visit(this);
}

std::string Binary::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

InterpreterValueType Binary::accept(Visitor<InterpreterValueType>* visitor)
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

InterpreterValueType Variable::accept(Visitor<InterpreterValueType>* visitor)
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

InterpreterValueType Assign::accept(Visitor<InterpreterValueType>* visitor)
{
	return visitor->visit(this);
}

std::string Assign::accept(Visitor<std::string>* visitor)
{
	return std::string();
}

Logical::Logical(Expr* left, Token* _operator, Expr* right) : left(left), _operator(_operator), right(right)
{

}

std::string Logical::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}

InterpreterValueType Logical::accept(Visitor<InterpreterValueType>* visitor)
{
	return visitor->visit(this);
}

Call::Call(Expr* callee, Token* paren, vector<Expr*> arguments) : callee(callee), paren(paren),
																  arguments(std::move(arguments))
{

}

InterpreterValueType Call::accept(Visitor<InterpreterValueType>* visitor)
{
	return visitor->visit(this);
}

std::string Call::accept(Visitor<std::string>* visitor)
{
	return visitor->visit(this);
}
