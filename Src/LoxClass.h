//
// Created by tao on 2021/4/7.
//

#ifndef JLOXTESTS_LOXCLASS_H
#define JLOXTESTS_LOXCLASS_H

#include <string>
#include <utility>
#include "LoxCallable.h"
#include "LoxFunction.h"

using std::string;
using std::map;


class LoxClass : public LoxCallable
{
private:
	map<string, LoxFunction*> methods {};
public:
	explicit LoxClass(string name, map<string, LoxFunction*> methods);
	[[nodiscard]] LoxFunction* findMethod(const string& methodName) const;
	LoxType call(Interpreter *interpreter, vector<LoxType> arguments) override;
	int arity() override;

	string name;
};


#endif //JLOXTESTS_LOXCLASS_H
