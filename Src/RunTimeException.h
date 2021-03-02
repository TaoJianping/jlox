//
// Created by tao on 2021/3/2.
//

#ifndef JLOXTESTS_RUNTIMEEXCEPTION_H
#define JLOXTESTS_RUNTIMEEXCEPTION_H


#include <stdexcept>
#include "Token.h"

class RunTimeException: public std::runtime_error
{
private:
	Lexeme::Token* token;
public:
	RunTimeException(const std::string& message, Lexeme::Token* t);
	int32_t getLine();
};


#endif //JLOXTESTS_RUNTIMEEXCEPTION_H
