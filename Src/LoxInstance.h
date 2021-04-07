//
// Created by tao on 2021/4/7.
//

#ifndef JLOXTESTS_LOXINSTANCE_H
#define JLOXTESTS_LOXINSTANCE_H

#include "LoxClass.h"


class LoxInstance
{
private:
	const LoxClass* klass;
public:
	explicit LoxInstance(const LoxClass* klass);
	string toString();
};


#endif //JLOXTESTS_LOXINSTANCE_H
