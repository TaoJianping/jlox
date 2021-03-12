//
// Created by tao on 2021/3/12.
//

#include "LoxFunction.h"
#include "Environment.h"
#include "ReturnStatement.h"
#include "variant"

LoxFunction::LoxFunction(const Function* declaration): declaration(declaration)
{

}

LoxType LoxFunction::call(Interpreter* interpreter, vector<LoxType> arguments)
{
	auto data = std::get<double>(arguments[0]);
	auto environment = Environment(interpreter->getGlobalEnvironment());
	for (size_t i = 0; i < declaration->params.size(); ++i)
	{
		environment.define(declaration->params.at(i)->getLexeme(), arguments.at(i));
	}

	try
	{
		interpreter->executeBlock(declaration->body, &environment);
	}
	catch (ReturnStatement& returnStatement)
	{
		return returnStatement.value;
	}

	return LoxType{std::monostate{}};
}

int LoxFunction::arity()
{
	return this->declaration->params.size();
}
