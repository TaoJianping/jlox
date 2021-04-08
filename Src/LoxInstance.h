//
// Created by tao on 2021/4/7.
//

#ifndef JLOXTESTS_LOXINSTANCE_H
#define JLOXTESTS_LOXINSTANCE_H

#include "LoxClass.h"

using std::map;
using std::string;

class LoxInstance
{
private:
	const LoxClass* klass;
	map<string, LoxType> fields {};
public:
	LoxType get(Token* name);
	void set(Token* name, LoxType value);
	explicit LoxInstance(const LoxClass* klass);
	string toString();
};


#endif //JLOXTESTS_LOXINSTANCE_H
