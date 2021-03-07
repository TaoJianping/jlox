//
// Created by taojianping on 2019/9/7.
//

#include "Expr.h"

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
Assign::Assign(Token* name, Expr* value): name(name), value(value)
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
