//
// Created by tao on 2021/3/1.
//

#include "Interpreter.h"
#include "RunTimeException.h"
#include "Lox.h"

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
		this->checkNumberOperand(expr->m_operator, right);
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
	{
		this->checkNumberOperands(expr->m_operator, left, right);
		return std::get<double>(left) - std::get<double>(right);
	}

	case Lexeme::TokenType::SLASH:
	{
		this->checkNumberOperands(expr->m_operator, left, right);
		return std::get<double>(left) / std::get<double>(right);
	}
	case Lexeme::TokenType::STAR:
	{
		this->checkNumberOperands(expr->m_operator, left, right);
		return std::get<double>(left) * std::get<double>(right);
	}
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
		throw RunTimeException("Operands must be two numbers or two strings.", expr->m_operator);
	}
	case Lexeme::TokenType::GREATER:
	{
		this->checkNumberOperands(expr->m_operator, left, right);
		return std::get<double>(left) > std::get<double>(right);
	}
	case Lexeme::TokenType::GREATER_EQUAL:
	{
		this->checkNumberOperands(expr->m_operator, left, right);
		return std::get<double>(left) >= std::get<double>(right);
	}
	case Lexeme::TokenType::LESS:
	{
		this->checkNumberOperands(expr->m_operator, left, right);
		return std::get<double>(left) < std::get<double>(right);
	}
	case Lexeme::TokenType::LESS_EQUAL:
	{
		this->checkNumberOperands(expr->m_operator, left, right);
		return std::get<double>(left) <= std::get<double>(right);
	}
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

void Interpreter::interpret(Expr* expr)
{
	try
	{
		auto value = this->evaluate(expr);
		this->print(value);
	}
	catch (RunTimeException& exception)
	{
		Lox::runtimeError(exception);
	}

}

void Interpreter::checkNumberOperand(Lexeme::Token* _operator, const InterpreterValueType& right)
{
	if (right.index() == 2)
		return;
	throw RunTimeException("Operand must be a number.", _operator);
}

void Interpreter::checkNumberOperands(Lexeme::Token* _operator, const InterpreterValueType& left,
		const InterpreterValueType& right)
{
	if (right.index() == 2 && left.index() == 2)
		return;
	throw RunTimeException("Operand must be a number.", _operator);
}

void Interpreter::print(const InterpreterValueType& data)
{
	if (data.index() == 2) {
		std::cout << std::get<double>(data) << std::endl;
	} else if (data.index() == 3) {
		std::cout << std::get<std::string>(data) << std::endl;
	} else if (data.index() == 1){
		std::cout << std::get<bool>(data) << std::endl;
	}
}

void Interpreter::visit(const Expression* expr)
{
	this->evaluate(expr->expression);
}

void Interpreter::visit(const Print* expr)
{
	InterpreterValueType value = this->evaluate(expr->expression);
	this->print(value);
}

void Interpreter::visit(const Var* expr)
{

}

void Interpreter::evaluate(Stmt* expr)
{
	expr->accept(this);
}

