//
// Created by tao on 2021/3/5.
//

#ifndef JLOXTESTS_ENVIRONMENT_H
#define JLOXTESTS_ENVIRONMENT_H

#include <unordered_map>
#include <string>
#include <variant>

#include "Token.h"

using std::unordered_map;
using std::string;
using InterpreterValueType = std::variant<std::monostate, bool, double, std::string>;
using Lexeme::Token;


class Environment
{
private:
	unordered_map<string, InterpreterValueType> values;
	Environment* enclosing;
public:
	Environment();
	explicit Environment(Environment* enclosing);

	void define(const string& name, InterpreterValueType value);
	InterpreterValueType get(Token* name);
	void assign(Token* name, InterpreterValueType value);
};


#endif //JLOXTESTS_ENVIRONMENT_H
