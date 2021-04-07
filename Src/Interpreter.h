//
// Created by tao on 2021/3/1.
//

#ifndef JLOXTESTS_INTERPRETER_H
#define JLOXTESTS_INTERPRETER_H

#include "Expr.h"
#include "Stmt.h"
#include "Environment.h"
#include "Type.h"

#include <map>

using std::map;

class Interpreter : public Visitor<LoxType>, public StmtVisitor<void>
{
private:
	Environment* globals = new Environment();
	Environment* environment = this->globals;

	map<const Expr*, int> locals {};

	void print(const LoxType& data);
	LoxType evaluate(Expr* expr);
	void execute(Stmt* expr);
	bool isTruthy(LoxType object);
	bool isEqual(const LoxType& a, const LoxType& b);
	void checkNumberOperand(Lexeme::Token* _operator, const LoxType& right);
	void checkNumberOperands(Lexeme::Token* _operator, const LoxType& left, const LoxType& right);
	LoxType lookUpVariable(Token* name, const Expr* expr);
public:
	[[nodiscard]] Environment* getGlobalEnvironment() const;
	[[nodiscard]] Environment* getEnvironment() const;
	void executeBlock(vector<Stmt*> statements, Environment* env);
	void resolve(const Expr* expr, int depth);

	LoxType visit(const Literal* expr) override;
	LoxType visit(const Grouping* expr) override;
	LoxType visit(const Unary* expr) override;
	LoxType visit(const Binary* expr) override;
	LoxType visit(const Variable* expr) override;
	LoxType visit(const Assign* expr) override;
	LoxType visit(const Logical* expr) override;
	LoxType visit(const Call* expr) override;

	void visit(const Block *expr) override;
	void visit(const Class *expr) override;
	void visit(const Expression *expr) override;
	void visit(const Print *expr) override;
	void visit(const Var *expr) override;
	void visit(const Function *expr) override;
	void visit(const Return *expr) override;
	void visit(const If *expr) override;
	void visit(const While *expr) override;

	void interpret(Expr* expr);
	void interpret(const vector<Stmt*>& statements);

	Interpreter();
	~Interpreter();
};


#endif //JLOXTESTS_INTERPRETER_H
