//
// Created by tao on 2021/4/7.
//

#include "LoxInstance.h"

#include <utility>
#include "RunTimeException.h"

LoxInstance::LoxInstance(const LoxClass* klass): klass(klass)
{

}

string LoxInstance::toString()
{
	return this->klass->name + " instance";
}

LoxType LoxInstance::get(Token* name)
{
	if (this->fields.find(name->getLexeme()) != this->fields.end())
	{
		return this->fields.at(name->getLexeme());
	}

	LoxFunction* method = this->klass->findMethod(name->getLexeme());
	if (method != nullptr)
		return method->bind(this);

	throw RunTimeException("Undefined property '" + name->getLexeme() + "'.", name);
}

void LoxInstance::set(Token* name, LoxType value)
{
	this->fields[name->getLexeme()] = std::move(value);
}
