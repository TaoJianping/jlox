//
// Created by tao on 2021/2/24.
//

#ifndef JLOXTESTS_ASTPRINTER_H
#define JLOXTESTS_ASTPRINTER_H

#include "Expr.h"


class AstPrinter : public Visitor<std::string>
{
public:
	std::string print(Expr &expr)
	{
		return expr.accept(this);
	}

	std::string visit(const Unary *) override;
	std::string visit(const Binary *) override;
	std::string visit(const Grouping *) override;
	std::string visit(const Literal *) override;
	std::string visit(const Variable *) override;
	std::string visit(const Assign *expr) override;
	std::string visit(const Logical *expr) override;
	std::string visit(const Call *expr) override;
	std::string visit(const Get *expr) override;
	std::string visit(const Set *expr) override;
	std::string visit(const This *expr) override;

	std::string parenthesize(const std::string& name, const std::vector<Expr*>& exprList);
};


#endif //JLOXTESTS_ASTPRINTER_H
