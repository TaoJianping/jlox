//
// Created by tao on 2021/3/11.
//

#include <chrono>
#include "LoxCallable.h"

int NativeClockFunction::arity()
{
	return 0;
}

LoxType NativeClockFunction::call(Interpreter* interpreter, vector<LoxType> arguments)
{
	return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count()) / 1000.0;
}
