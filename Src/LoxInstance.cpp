//
// Created by tao on 2021/4/7.
//

#include "LoxInstance.h"

LoxInstance::LoxInstance(const LoxClass* klass): klass(klass)
{

}

string LoxInstance::toString()
{
	return this->klass->name + " instance";
}
