//
// Created by tao on 2021/3/1.
//

#ifndef JLOXTESTS_INTERPRETER_H
#define JLOXTESTS_INTERPRETER_H

#include "Expr.h"


class Interpreter : public Visitor<InterpreterValueType>
{
private:
	InterpreterValueType evaluate(Expr* expr);
	bool isTruthy(InterpreterValueType object);
	bool isEqual(const InterpreterValueType& a, const InterpreterValueType& b);
public:
	InterpreterValueType visit(const Literal* expr) override;
	InterpreterValueType visit(const Grouping* expr) override;
	InterpreterValueType visit(const Unary* expr) override;
	InterpreterValueType visit(const Binary* expr) override;

};


#endif //JLOXTESTS_INTERPRETER_H
