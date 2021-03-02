//
// Created by tao on 2021/3/2.
//

#include "RunTimeException.h"

RunTimeException::RunTimeException(const std::string& message, Lexeme::Token* t) : runtime_error(message)
{
	this->token = t;
}

int32_t RunTimeException::getLine()
{
	return this->token->getLine();
}
