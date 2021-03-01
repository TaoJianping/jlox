//
// Created by tao on 2021/3/1.
//

#include "Interpreter.h"

InterpreterValueType Interpreter::visit(const Literal* expr)
{
	auto res = expr->value->getLiteral();
	return res;
}

InterpreterValueType Interpreter::visit(const Grouping* expr)
{
	return this->evaluate(expr->expression);
}

InterpreterValueType Interpreter::evaluate(Expr* expr)
{
	return expr->accept(this);
}

InterpreterValueType Interpreter::visit(const Unary* expr)
{
	auto right = this->evaluate(expr->right);

	switch (expr->m_operator->getType())
	{
	case Lexeme::TokenType::MINUS:
	{
		double num = std::get<double>(right);
		return -num;
	}
	case Lexeme::TokenType::BANG:
	{
		return !this->isTruthy(right);
	}
	}

	return nullptr;
}

InterpreterValueType Interpreter::visit(const Binary* expr)
{
	auto left = this->evaluate(expr->left);
	auto right = this->evaluate(expr->right);

	switch (expr->m_operator->getType())
	{
	case Lexeme::TokenType::MINUS:
		return std::get<double>(left) - std::get<double>(right);
	case Lexeme::TokenType::SLASH:
		return std::get<double>(left) / std::get<double>(right);
	case Lexeme::TokenType::STAR:
		return std::get<double>(left) * std::get<double>(right);
	case Lexeme::TokenType::PLUS:
	{
		if (left.index() == 2 && right.index() == 2)
		{
			return std::get<double>(left) + std::get<double>(right);
		}
		if (left.index() == 3 && right.index() == 3)
		{
			return std::get<std::string>(left) + std::get<std::string>(right);
		}
	}
	case Lexeme::TokenType::GREATER:
		return std::get<double>(left) > std::get<double>(right);
	case Lexeme::TokenType::GREATER_EQUAL:
		return std::get<double>(left) >= std::get<double>(right);
	case Lexeme::TokenType::LESS:
		return std::get<double>(left) < std::get<double>(right);
	case Lexeme::TokenType::LESS_EQUAL:
		return std::get<double>(left) <= std::get<double>(right);
	case Lexeme::TokenType::BANG_EQUAL:
		return !this->isEqual(left, right);
	case Lexeme::TokenType::EQUAL_EQUAL:
		return this->isEqual(left, right);
	}

	return nullptr;
}

bool Interpreter::isEqual(const InterpreterValueType& a, const InterpreterValueType& b)
{
	if (a.index() == 1 && b.index() == 1)
		return true;
	if (a.index() == 1)
		return false;

	return a == b;
}


bool Interpreter::isTruthy(InterpreterValueType _object)
{
	if (_object.index() == 0)
	{
		return false;
	}

	if (_object.index() == 1)
	{
		return std::get<bool>(_object);
	}

	return true;
}

