//
// Created by tao on 2021/3/11.
//

#ifndef JLOXTESTS_TYPE_H
#define JLOXTESTS_TYPE_H

#include <variant>

class LoxCallable;

class test {
	virtual int a() = 0;
};

using LoxType = std::variant<std::monostate, bool, double, std::string, LoxCallable*>;


#endif //JLOXTESTS_TYPE_H
