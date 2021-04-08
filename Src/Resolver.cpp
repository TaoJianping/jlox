//

#include "Resolver.h"
#include "Lox.h"

Resolver::Resolver(Interpreter* interpreter): interpreter(interpreter)
{

}

void Resolver::visit(const Block* expr)
{
	this->beginScope();
	this->resolve(expr->statements);
	this->endScope();
}

void Resolver::resolve(const vector<Stmt*>& statements)
{
	for (auto & statement : statements)
	{
		this->resolve(statement);
	}
}

void Resolver::resolve(Stmt* statement)
{
	statement->accept(this);
}

void Resolver::resolve(Expr* statement)
{
	statement->accept(this);
}

void Resolver::beginScope()
{
	this->scopes.push_back(new map<string, bool> {});
}

void Resolver::endScope()
{
	auto top = this->scopes.back();
	this->scopes.pop_back();
	delete top;
}

void Resolver::visit(const Var* expr)
{
	this->declare(expr->name);
	if (expr->initializer != nullptr)
	{
		this->resolve(expr->initializer);
	}
	this->define(expr->name);
}

void Resolver::declare(Token* name)
{
	if (this->scopes.empty())
		return;
	auto scope = this->scopes.back();

	if (scope->count(name->getLexeme())) {
		Lox::error(name,
				"Already variable with this name in this scope.");
	}

	scope->insert({name->getLexeme(), false});
}

void Resolver::define(Token* name)
{
	if (this->scopes.empty())
		return;

	this->scopes.back()->at(name->getLexeme()) = true;
}

void Resolver::visit(const Variable* expr)
{
	// If the variable exists in the current scope but its value is false,
	// that means we have declared it but not yet defined it.
	if (!this->scopes.empty()
		&& this->scopes.back()->count(expr->name->getLexeme()) > 0
		&& this->scopes.back()->at(expr->name->getLexeme()) == false)
	{
		Lox::error(expr->name, "Can't read local variable in its own initializer.");
	}

	this->resolveLocal(expr, expr->name);
}

void Resolver::resolveLocal(const Expr* expr, Token* name)
{
	for (int i = this->scopes.size() - 1; i >= 0; i--)
	{
		if (this->scopes.at(i)->count(name->getLexeme())) {
			this->interpreter->resolve(expr, this->scopes.size() - 1 - i);
		}
	}
}

void Resolver::visit(const Assign* expr)
{
	this->resolve(expr->value);
	this->resolveLocal(expr, expr->name);
}

//
// Created by tao on 2021/3/15.
void Resolver::visit(const Function* expr)
{
	this->declare(expr->name);
	this->define(expr->name);

	this->resolveFunction(expr, FunctionType::FUNCTION);
}

void Resolver::resolveFunction(const Function* function, FunctionType functionType)
{
	FunctionType enclosingFunction = currentFunction;
	currentFunction = functionType;

	this->beginScope();

	for (Token* param : function->params)
	{
		this->declare(param);
		this->define(param);
	}

	this->resolve(function->body);
	this->endScope();
	currentFunction = enclosingFunction;
}

void Resolver::visit(const Expression* expr)
{
	this->resolve(expr->expression);
}

void Resolver::visit(const If* expr)
{
	this->resolve(expr->condition);
	this->resolve(expr->thenBranch);
}

void Resolver::visit(const Print* expr)
{
	this->resolve(expr->expression);
}

void Resolver::visit(const Return* expr)
{
	if (this->currentFunction == FunctionType::NONE) {
		Lox::error(expr->keyword, "Can't return from top-level code.");
	}

	if (expr->value != nullptr) {
		this->resolve(expr->value);
	}
}

void Resolver::visit(const While* expr)
{
	this->resolve(expr->condition);
	this->resolve(expr->body);
}

void Resolver::visit(const Binary* expr)
{
	this->resolve(expr->left);
	this->resolve(expr->right);
}

void Resolver::visit(const Call* expr)
{
	this->resolve(expr->callee);

	for (auto argument : expr->arguments)
	{
		this->resolve(argument);
	}
}

void Resolver::visit(const Grouping* expr)
{
	this->resolve(expr->expression);
}

void Resolver::visit(const Literal* expr)
{

}

void Resolver::visit(const Logical* expr)
{
	this->resolve(expr->left);
	this->resolve(expr->right);
}

void Resolver::visit(const Unary* expr)
{
	this->resolve(expr->right);
}

void Resolver::visit(const Class* expr)
{
	this->declare(expr->name);
	this->define(expr->name);

	for (auto method : expr->methods)
	{
		auto declaration = FunctionType::METHOD;
		this->resolveFunction(method, declaration);
	}
}

void Resolver::visit(const Get* expr)
{
	this->resolve(expr->object);
}

void Resolver::visit(const Set* expr)
{
	this->resolve(expr->value);
	this->resolve(expr->object);
}
