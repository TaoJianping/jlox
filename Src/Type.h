//
// Created by tao on 2021/3/11.
//

#ifndef JLOXTESTS_TYPE_H
#define JLOXTESTS_TYPE_H

#include <variant>
//#include "LoxClass.h"

class LoxCallable;
class LoxClass;
class LoxInstance;

enum class LoxTypeIndex : size_t
{
	Nil,
	Bool,
	Number,
	String,
	Function,
	Class,
	Instance,
};

using LoxType = std::variant<std::monostate, bool, double, std::string, LoxCallable*, LoxClass*, LoxInstance*>;


#endif //JLOXTESTS_TYPE_H
