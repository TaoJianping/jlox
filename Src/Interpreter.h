//
// Created by tao on 2021/3/1.
//

#ifndef JLOXTESTS_INTERPRETER_H
#define JLOXTESTS_INTERPRETER_H

#include "Expr.h"
#include "Stmt.h"

class Interpreter : public Visitor<InterpreterValueType>, public StmtVisitor<void>
{
private:
	void print(const InterpreterValueType& data);
	InterpreterValueType evaluate(Expr* expr);
	void evaluate(Stmt* expr);
	bool isTruthy(InterpreterValueType object);
	bool isEqual(const InterpreterValueType& a, const InterpreterValueType& b);
	void checkNumberOperand(Lexeme::Token* _operator, const InterpreterValueType& right);
	void checkNumberOperands(Lexeme::Token* _operator, const InterpreterValueType& left, const InterpreterValueType& right);
public:
	InterpreterValueType visit(const Literal* expr) override;
	InterpreterValueType visit(const Grouping* expr) override;
	InterpreterValueType visit(const Unary* expr) override;
	InterpreterValueType visit(const Binary* expr) override;

	void visit(const Expression *expr) override;
	void visit(const Print *expr) override;
	void visit(const Var *expr) override;

	void interpret(Expr* expr);
};


#endif //JLOXTESTS_INTERPRETER_H
