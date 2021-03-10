//
// Created by tjp56 on 2021/2/26.
//

#ifndef JLOX_PARSER_H
#define JLOX_PARSER_H

#include <vector>
#include <string>

#include "Token.h"
#include "Expr.h"
#include "Stmt.h"

using Lexeme::Token;
using Lexeme::TokenType;
using std::vector;

//program        → statement* EOF ;
//
//statement      → exprStmt
//				| printStmt ;
//
//exprStmt       → expression ";" ;
//printStmt      → "print" expression ";" ;

//program        → declaration* EOF ;
//
//declaration    → varDecl
//               | statement ;
//
//statement      → exprStmt
//               | printStmt ;
//
//varDecl        → "var" IDENTIFIER ( "=" expression )? ";" ;




class ParseException : std::exception {
};


class Parser {
private:
	std::vector<Lexeme::Token *> tokens;
	int current;

	Expr* expression();

	Expr* assignment();

	Expr* equality();

	Expr* _or();

	Expr* _and();

	Expr* comparison();

	Expr* term();

	Expr* factor();

	Expr* unary();

	Expr* primary();

	Stmt* statement();

	vector<Stmt*> block();

	Stmt* declaration();

	Stmt* varDeclaration();

	Stmt* expressionStatement();

	Stmt* printStatement();

	Stmt* whileStatement();

	Stmt* ifStatement();

	Stmt* forStatement();

	Token* consume(TokenType, const std::string &);

	ParseException error(const Token* token, const std::string &);

	bool match(const std::vector<TokenType>& );

	bool match(TokenType);

	bool check(TokenType type);

	Token* advance();

	bool isAtEnd();

	Token* peek();

	Token* previous();

	void synchronize();

public:
	vector<Stmt*> parse();

	explicit Parser(const std::vector<Token *> &ts) {
		tokens = ts;
		current = 0;
	}
};


#endif //JLOX_PARSER_H
