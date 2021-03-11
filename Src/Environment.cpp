//
// Created by tao on 2021/3/5.
//

#include "Environment.h"

#include <utility>
#include "RunTimeException.h"

void Environment::define(const string& name, LoxType value)
{
	this->values[name] = std::move(value);
}

LoxType Environment::get(Token* name)
{
	if (values.count(name->getLexeme()))
	{
		return values.at(name->getLexeme());
	}

	if (this->enclosing != nullptr)
	{
		return this->enclosing->get(name);
	}

	throw RunTimeException("Undefined variable '" + name->getLexeme() + "'.", name);
}

void Environment::assign(Token* name, LoxType value)
{
	if (this->values.count(name->getLexeme()))
	{
		values[name->getLexeme()] = value;
		return;
	}

	if (this->enclosing != nullptr)
	{
		this->enclosing->assign(name, value);
		return;
	}

	throw RunTimeException("Undefined variable '" + name->getLexeme() + "'.", name);
}

Environment::Environment()
{
	this->enclosing = nullptr;
}

Environment::Environment(Environment* enclosing)
{
	this->enclosing = enclosing;
};
