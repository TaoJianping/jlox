//
// Created by tao on 2021/3/15.
//

#ifndef JLOXTESTS_RESOLVER_H
#define JLOXTESTS_RESOLVER_H

#include <vector>
#include <stack>
#include <map>
#include <string>

#include "Expr.h"
#include "Stmt.h"
#include "Interpreter.h"

using std::vector;
using std::stack;
using std::map;
using std::string;

enum class FunctionType {
	NONE,
	FUNCTION
};

class Resolver: public Visitor<void>, public StmtVisitor<void>
{
private:
	Interpreter* interpreter;
	void beginScope();
	void endScope();

	void declare(Token* name);
	void define(Token* name);
	void resolveLocal(const Expr* expr, Token* name);
	void resolveFunction(const Function* function, FunctionType functionType);
	vector<map<string, bool>* > scopes {};
	FunctionType currentFunction = FunctionType::NONE;
public:
	void resolve(Stmt* statement);
	void resolve(Expr* statement);
	void resolve(const vector<Stmt*>& statements);

	explicit Resolver(Interpreter* interpreter);
	void visit(const Block *expr) override;
	void visit(const Var *expr) override;
	void visit(const Variable *expr) override;
	void visit(const Assign *expr) override;
	void visit(const Function *expr) override;
	void visit(const Expression *expr) override;
	void visit(const If *expr) override;
	void visit(const Print *expr) override;
	void visit(const Return *expr) override;
	void visit(const While *expr) override;
	void visit(const Binary *expr) override;
	void visit(const Call *expr) override;
	void visit(const Grouping *expr) override;
	void visit(const Literal *expr) override;
	void visit(const Logical *expr) override;
	void visit(const Unary *expr) override;
};


#endif //JLOXTESTS_RESOLVER_H
