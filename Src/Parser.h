//
// Created by tjp56 on 2021/2/26.
//

#ifndef JLOX_PARSER_H
#define JLOX_PARSER_H

#include <vector>
#include <string>

#include "Token.h"
#include "Expr.h"

class ParseException : std::exception {
};


class Parser {
	using Token = Lexeme::Token;
	using TokenType = Lexeme::TokenType;
private:
	std::vector<Lexeme::Token *> tokens;
	int current;

	Expr* expression();

	Expr* equality();

	Expr* comparison();

	Expr* term();

	Expr* factor();

	Expr* unary();

	Expr* primary();

	Token* consume(TokenType, const std::string &);

	ParseException error(const Token* token, const std::string &);

	bool match(const std::vector<TokenType>& );

	bool match(TokenType);

	bool check(TokenType type);

	Token* advance();

	bool isAtEnd();

	Token* peek();

	Token* previous();


public:
	Expr *parse();

	explicit Parser(const std::vector<Token *> &ts) {
		tokens = ts;
		current = 0;
	}
};


#endif //JLOX_PARSER_H