//
// Created by tao on 2021/2/24.
//

#include "AstPrinter.h"


std::string AstPrinter::visit(const Literal* literal)
{
	if (literal->value->getType() == Lexeme::TokenType::STRING)
	{
		return std::get<std::string>(literal->value->getLiteral());
	}
	if (literal->value->getType() == Lexeme::TokenType::NUMBER)
	{
		return std::to_string(std::get<double>(literal->value->getLiteral()));
	}
	return "";
}

std::string AstPrinter::visit(const Unary* unary)
{
	return this->parenthesize(unary->m_operator->getLexeme(), {unary->right});
}

std::string AstPrinter::visit(const Binary* binary)
{
	return this->parenthesize(binary->m_operator->getLexeme(), {binary->left, binary->right});
}

std::string AstPrinter::visit(const Grouping* group)
{
	return this->parenthesize("group", {group->expression});
}

std::string AstPrinter::parenthesize(const std::string& name, const std::vector<Expr*>& expr)
{
	std::string res;

	res += '(';
	res += name;

	for (auto e : expr)
	{
		res += ' ';
		res += e->accept(this);
	}

	res.append(")");

	return res;
}

std::string AstPrinter::visit(const Variable*)
{
	return std::string();
}

std::string AstPrinter::visit(const Assign* expr)
{
	return std::string();
}

std::string AstPrinter::visit(const Logical* expr)
{
	return std::string();
}

std::string AstPrinter::visit(const Call* expr)
{
	return std::string();
}

std::string AstPrinter::visit(const Get* expr)
{
	return std::__cxx11::string();
}

std::string AstPrinter::visit(const Set* expr)
{
	return std::__cxx11::string();
}
