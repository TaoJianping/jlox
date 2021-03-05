//
// Created by tao on 2021/3/5.
//

#include "Environment.h"
#include "RunTimeException.h"

void Environment::define(const string& name, InterpreterValueType value)
{
	this->values[name] = value;
}

InterpreterValueType Environment::get(Token* name)
{
	if (values.count(name->getLexeme())) {
		return values.at(name->getLexeme());
	}

	throw RunTimeException("Undefined variable '" + name->getLexeme() + "'.", name);
};
