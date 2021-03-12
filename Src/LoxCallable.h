//
// Created by tao on 2021/3/11.
//

#ifndef JLOXTESTS_LOXCALLABLE_H
#define JLOXTESTS_LOXCALLABLE_H

#include <vector>
#include <variant>
#include <string>
#include "Type.h"
#include "Interpreter.h"

using std::vector;

class LoxCallable
{
public:
	virtual int arity() = 0;
	virtual LoxType call(Interpreter* interpreter, vector<LoxType> arguments) = 0;
};


class NativeClockFunction : public LoxCallable
{
public:
	int arity() override;
	LoxType call(Interpreter *interpreter, vector<LoxType> arguments) override;
};


#endif //JLOXTESTS_LOXCALLABLE_H
