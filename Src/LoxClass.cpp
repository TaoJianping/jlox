//
// Created by tao on 2021/4/7.
//

#include "LoxClass.h"
#include "LoxInstance.h"

LoxClass::LoxClass(string name) : name(std::move(name))
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
