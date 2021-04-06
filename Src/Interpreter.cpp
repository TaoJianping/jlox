//
// Created by tao on 2021/3/1.
//

#include <memory>
#include "Interpreter.h"
#include "RunTimeException.h"
#include "Lox.h"
#include "LoxCallable.h"
#include "LoxFunction.h"
#include "ReturnStatement.h"
#include <sstream>

LoxType Interpreter::visit(const Literal* expr)
{
	auto res = expr->value->getLiteral();
	return res;
}

LoxType Interpreter::visit(const Grouping* expr)
{
	return this->evaluate(expr->expression);
}

LoxType Interpreter::evaluate(Expr* expr)
{
	return expr->accept(this);
}

LoxType Interpreter::visit(const Unary* expr)
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

LoxType Interpreter::visit(const Binary* expr)
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

bool Interpreter::isEqual(const LoxType& a, const LoxType& b)
{
	if (a.index() == 1 && b.index() == 1)
		return true;
	if (a.index() == 1)
		return false;

	return a == b;
}

bool Interpreter::isTruthy(LoxType _object)
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

void Interpreter::checkNumberOperand(Lexeme::Token* _operator, const LoxType& right)
{
	if (right.index() == 2)
		return;
	throw RunTimeException("Operand must be a number.", _operator);
}

void Interpreter::checkNumberOperands(Lexeme::Token* _operator, const LoxType& left,
		const LoxType& right)
{
	if (right.index() == 2 && left.index() == 2)
		return;
	throw RunTimeException("Operand must be a number.", _operator);
}

void Interpreter::print(const LoxType& data)
{
	if (data.index() == 2)
	{
		std::cout << std::get<double>(data) << std::endl;
	}
	else if (data.index() == 3)
	{
		std::cout << std::get<std::string>(data) << std::endl;
	}
	else if (data.index() == 1)
	{
		auto v = std::get<bool>(data);
		if (v)
		{
			std::cout << "true" << std::endl;
		}
		else
		{
			std::cout << "false" << std::endl;
		}
	}
	else if (data.index() == (size_t)LoxTypeIndex::Function)
	{
		LoxCallable* function = std::get<LoxCallable*>(data);
		std::cout << dynamic_cast<LoxFunction*>(function) << std::endl;
	}
	else if (data.index() == 0)
	{
		std::cout << "nil" << std::endl;
	}
}

void Interpreter::visit(const Expression* expr)
{
	this->evaluate(expr->expression);
}

void Interpreter::visit(const Print* expr)
{
	LoxType value = this->evaluate(expr->expression);
	this->print(value);
}

void Interpreter::visit(const Var* expr)
{
	LoxType value = std::monostate();
	if (expr->initializer != nullptr)
	{
		value = this->evaluate(expr->initializer);
	}
	environment->define(expr->name->getLexeme(), value);
}

void Interpreter::execute(Stmt* expr)
{
	expr->accept(this);
}

void Interpreter::interpret(const vector<Stmt*>& statements)
{
	try
	{
		for (auto statement : statements)
		{
			this->execute(statement);
		}
	}
	catch (RunTimeException& exception)
	{
		Lox::runtimeError(exception);
	}
}

LoxType Interpreter::visit(const Variable* expr)
{
//	return this->environment->get(expr->name);
	return this->lookUpVariable(expr->name, expr);
}

LoxType Interpreter::visit(const Assign* expr)
{
	LoxType value = this->evaluate(expr->value);
//	this->environment->assign(expr->name, value);
	auto contains = locals.find(expr);

	if (contains != locals.end())
	{
		environment->assignAt(locals.at(expr), expr->name, value);
	}
	else
	{
		globals->assign(expr->name, value);
	}

	return value;
}

void Interpreter::visit(const Block* expr)
{
	auto newEnvironment = new Environment(this->environment);
	this->executeBlock(expr->statements, newEnvironment);
	delete newEnvironment;
}

void Interpreter::executeBlock(vector<Stmt*> statements, Environment* env)
{
	auto previousEnv = this->environment;
	try
	{
		this->environment = env;
		for (auto& statement : statements)
		{
			this->execute(statement);
		}
		this->environment = previousEnv;
	}
	catch (RunTimeException& exception)
	{
		Lox::runtimeError(exception);
		std::cout << "Found Block Fault" << std::endl;
		this->environment = previousEnv;
	}
	catch (ReturnStatement& returnStatement)
	{
		this->environment = previousEnv;
		throw ReturnStatement(returnStatement.value);
	}
}

void Interpreter::visit(const If* expr)
{
	if (isTruthy(this->evaluate(expr->condition)))
	{
		this->execute(expr->thenBranch);
	}
	else if (expr->elseBranch != nullptr)
	{
		this->execute(expr->elseBranch);
	}
}

LoxType Interpreter::visit(const Logical* expr)
{
	auto left = this->evaluate(expr->left);

	if (expr->_operator->getType() == TokenType::OR)
	{
		if (this->isTruthy(left)) return left;
	}
	else
	{
		if (!this->isTruthy(left)) return left;
	}

	return this->evaluate(expr->right);
}

void Interpreter::visit(const While* expr)
{
	while (this->isTruthy(this->evaluate(expr->condition)))
	{
		this->execute(expr->body);
	}
}

LoxType Interpreter::visit(const Call* expr)
{
	LoxType callee = this->evaluate(expr->callee);

	vector<LoxType> arguments;
	for (auto& argument : expr->arguments)
	{
		arguments.push_back(this->evaluate(argument));
	}

	if (callee.index() != (size_t)LoxTypeIndex::Function)
	{
		throw RunTimeException("Can only call functions and classes.", expr->paren);
	}

	LoxCallable* function = std::get<LoxCallable*>(callee);
	if (arguments.size() != function->arity())
	{
		std::ostringstream stringStream;
		stringStream << "Expected " << function->arity()
					 << " arguments but got " << arguments.size() << ".";
		throw RunTimeException(stringStream.str(), expr->paren);
	}

	return function->call(this, arguments);
}

Interpreter::Interpreter()
{
	this->globals->define("clock", new NativeClockFunction());
}

Interpreter::~Interpreter()
{
	delete this->globals;
}

Environment* Interpreter::getGlobalEnvironment() const
{
	return this->globals;
}

void Interpreter::visit(const Function* stmt)
{
	auto function = new LoxFunction(stmt, this->environment);
	this->environment->define(stmt->name->getLexeme(), function);
}

void Interpreter::visit(const Return* expr)
{
	LoxType value = std::monostate();
	if (expr->value != nullptr)
		value = this->evaluate(expr->value);

	throw ReturnStatement(value);
}

Environment* Interpreter::getEnvironment() const
{
	return this->environment;
}

void Interpreter::resolve(const Expr* expr, int depth)
{
	this->locals[expr] = depth;
}

LoxType Interpreter::lookUpVariable(Token* name, const Expr* expr)
{
//	int distance = locals.at(expr);
	auto contains = locals.find(expr);

	if (contains != locals.end())
	{
		return this->environment->getAt(this->locals.at(expr), name->getLexeme());
	}
	else
	{
		return this->globals->get(name);
	}
}

