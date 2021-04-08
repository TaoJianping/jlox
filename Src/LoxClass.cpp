//
// Created by tao on 2021/4/7.
//

#include "LoxClass.h"

#include <utility>
#include "LoxInstance.h"

LoxClass::LoxClass(string name, map<string, LoxFunction*> methods) : name(std::move(name)), methods(std::move(methods))
{

}

int LoxClass::arity()
{
	return 0;
}

LoxType LoxClass::call(Interpreter* interpreter, vector<LoxType> arguments)
{
	auto instance = new LoxInstance(this);
	return instance;
}

LoxFunction* LoxClass::findMethod(const string& methodName) const
{
	if (this->methods.find(methodName) != this->methods.end())
	{
		return methods.at(methodName);
	}

	return nullptr;
}
