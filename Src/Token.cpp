//
// Created by taojianping on 2019/8/19.
//
#include "Token.h"

#include <utility>

std::string Lexeme::Token::toString()
{
	return nullptr;
}

Lexeme::Token::Token(Lexeme::TokenType t, std::string lexeme, std::variant<std::monostate, std::string, double> ll, int l) :
		type(t), lexeme(std::move(lexeme)), literal(std::move(ll)), line(l)
{

}

Lexeme::TokenType Lexeme::Token::getType()
{
	return this->type;
}
