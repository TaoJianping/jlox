//
// Created by tao on 2021/3/12.
//

#ifndef JLOXTESTS_RETURNSTATEMENT_H
#define JLOXTESTS_RETURNSTATEMENT_H

#include <stdexcept>
#include <utility>
#include "Type.h"

class ReturnStatement : public std::runtime_error
{
public:
	LoxType value;
	explicit ReturnStatement(LoxType v) : runtime_error("Return sentinel") {
		this->value = std::move(v);
	}
};


#endif //JLOXTESTS_RETURNSTATEMENT_H
