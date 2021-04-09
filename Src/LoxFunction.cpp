//
// Created by tao on 2021/3/12.
//

#include "LoxFunction.h"
#include "Environment.h"
#include "ReturnStatement.h"
#include "variant"

LoxFunction::LoxFunction(const Function* declaration, Environment* closure, bool isInitializer):
								declaration(declaration), closure(closure), isInitializer(isInitializer)
{

}

LoxType LoxFunction::call(Interpreter* interpreter, vector<LoxType> arguments)
{
	auto environment = new Environment(this->closure);
	for (size_t i = 0; i < declaration->params.size(); ++i)
	{
		environment->define(declaration->params.at(i)->getLexeme(), arguments.at(i));
	}

	try
	{
		interpreter->executeBlock(declaration->body, environment);
	}
	catch (ReturnStatement& returnStatement)
	{
		if (this->isInitializer)
			return this->closure->getAt(0, "this");
		return returnStatement.value;
	}
	if (this->isInitializer) return closure->getAt(0, "this");
	return LoxType{std::monostate{}};
}

int LoxFunction::arity()
{
	return this->declaration->params.size();
}

LoxFunction* LoxFunction::bind(LoxInstance* instance)
{
	auto environment = new Environment(this->closure);
	environment->define("this", instance);
	return new LoxFunction(this->declaration, environment, this->isInitializer);
}
