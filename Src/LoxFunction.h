//
// Created by tao on 2021/3/12.
//

#ifndef JLOXTESTS_LOXFUNCTION_H
#define JLOXTESTS_LOXFUNCTION_H

#include "LoxCallable.h"
#include "Stmt.h"

class LoxFunction : public LoxCallable
{
private:
public:
	const Function* declaration;
	Environment* closure;
	bool isInitializer;
	LoxFunction(const Function* declaration, Environment* closure, bool isInitializer);
	LoxFunction* bind(LoxInstance* instance);
	int arity() override;
	LoxType call(Interpreter *interpreter, vector<LoxType> arguments) override;

	friend std::ostream& operator<<(std::ostream& output, const LoxFunction& function)
	{
		output << "<fn " << function.declaration->name->getLexeme() << ">" << std::endl;
		return output;
	}
};


#endif //JLOXTESTS_LOXFUNCTION_H
