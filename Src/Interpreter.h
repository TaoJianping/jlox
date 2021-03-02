//
// Created by tao on 2021/3/1.
//

#ifndef JLOXTESTS_INTERPRETER_H
#define JLOXTESTS_INTERPRETER_H

#include "Expr.h"


class Interpreter : public Visitor<InterpreterValueType>
{
private:
	void print(const InterpreterValueType& data);
	InterpreterValueType evaluate(Expr* expr);
	bool isTruthy(InterpreterValueType object);
	bool isEqual(const InterpreterValueType& a, const InterpreterValueType& b);
	void checkNumberOperand(Lexeme::Token* _operator, const InterpreterValueType& right);
	void checkNumberOperands(Lexeme::Token* _operator, const InterpreterValueType& left, const InterpreterValueType& right);
public:
	InterpreterValueType visit(const Literal* expr) override;
	InterpreterValueType visit(const Grouping* expr) override;
	InterpreterValueType visit(const Unary* expr) override;
	InterpreterValueType visit(const Binary* expr) override;

	void interpret(Expr* expr);
};


#endif //JLOXTESTS_INTERPRETER_H
