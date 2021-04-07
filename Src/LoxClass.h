//
// Created by tao on 2021/4/7.
//

#ifndef JLOXTESTS_LOXCLASS_H
#define JLOXTESTS_LOXCLASS_H

#include <string>
#include <utility>
#include "LoxCallable.h"

using std::string;

class LoxClass : public LoxCallable
{
public:
	explicit LoxClass(string name);
	LoxType call(Interpreter *interpreter, vector<LoxType> arguments) override;
	int arity() override;

	string name;
};


#endif //JLOXTESTS_LOXCLASS_H
