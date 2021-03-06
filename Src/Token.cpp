//
// Created by taojianping on 2019/8/19.
//
#include "Token.h"

#include <utility>

std::string Lexeme::Token::toString()
{
	return nullptr;
}

Lexeme::Token::Token(Lexeme::TokenType t, std::string lexeme, LoxType ll, int l) :
		type(t), lexeme(std::move(lexeme)), literal(std::move(ll)), line(l)
{

}

Lexeme::TokenType Lexeme::Token::getType() const
{
	return this->type;
}

LoxType Lexeme::Token::getLiteral() const
{
	return this->literal;
}

std::string Lexeme::Token::getLexeme() const
{
	return this->lexeme;
}

int32_t Lexeme::Token::getLine() const
{
	return this->line;
}
