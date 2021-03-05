//
// Created by taojianping on 2019/9/11.
//

#include "Parser.h"

#include "Lox.h"
#include <utility>

//expression  -> equality ;
//equality    -> comparison ( ( "!=" | "==" ) comparison )* ;
//comparison  -> term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
//term        -> factor ( ( "-" | "+" ) factor )* ;
//factor      -> unary ( ( "/" | "*" ) unary )* ;
//unary       -> ( "!" | "-" ) unary
//					| primary ;
//primary     -> NUMBER | STRING | "true" | "false" | "nil"
//					| "(" expression ")" ;

vector<Stmt*> Parser::parse()
{
	vector<Stmt*> statements;
	try
	{
		while (!isAtEnd())
		{
			statements.push_back(declaration());
		}

		return statements;
	}
	catch (ParseException& pe)
	{
		return statements;
	}
}

Expr* Parser::expression()
{
	return equality();
}

/*
 * equality -> comparison ( ( "!=" | "==" ) comparison )* ;
 * */
Expr* Parser::equality()
{
	Expr* expr = comparison();

	while (this->match({ Lexeme::TokenType::BANG_EQUAL, Lexeme::TokenType::EQUAL_EQUAL }))
	{
		auto _operator = this->previous();
		auto right = this->comparison();
		expr = new Binary(expr, _operator, right);
	}

	return expr;
}

/*
 * comparison -> addition ( ( ">" | ">=" | "<" | "<=" ) addition )* ;
 * */
Expr* Parser::comparison()
{
	Expr* expr = this->term();

	while (match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL }))
	{
		auto _operator = this->previous();
		auto right = this->term();
		expr = new Binary(expr, _operator, right);
	}

	return expr;
}

/*
 * term -> factor ( ( "-" | "+" ) factor )* ;
 * */
Expr* Parser::term()
{
	auto expr = this->factor();

	while (this->match({ TokenType::MINUS, TokenType::PLUS }))
	{
		auto _operator = this->previous();
		auto right = this->factor();
		expr = new Binary(expr, _operator, right);
	}

	return expr;
}

/*
 * factor -> unary ( ( "/" | "*" ) unary )* ;
 * */
Expr* Parser::factor()
{
	auto expr = this->unary();

	while (this->match({ TokenType::SLASH, TokenType::STAR }))
	{
		auto _operator = this->previous();
		auto right = this->unary();
		expr = new Binary(expr, _operator, right);
	}

	return expr;
}

/*
 * unary -> ( "!" | "-" ) unary | primary ;
 * */
Expr* Parser::unary()
{
	while (this->match({ TokenType::BANG, TokenType::MINUS }))
	{
		auto _operator = this->previous();
		auto right = this->unary();
		return new Unary(_operator, right);
	}

	return this->primary();
}

/*
 * primary -> NUMBER | STRING | "false" | "true" | "nil" | "(" expression ")" ;
 * */
Expr* Parser::primary()
{

	if (match(TokenType::FALSE))
		return new Literal(this->previous());

	if (match(TokenType::TRUE))
		return new Literal(this->previous());

	if (match(TokenType::NIL))
		return new Literal(this->previous());

	if (match({ TokenType::STRING, TokenType::NUMBER }))
	{
		return new Literal(this->previous());
	}

	if (this->match(TokenType::IDENTIFIER))
	{
		return new Variable(previous());
	}

	if (match(TokenType::LEFT_PAREN))
	{
		Expr* expr = expression();
		consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
		return new Grouping(expr);
	}

	throw error(peek(), "Expect expression.");
}

Lexeme::Token* Parser::consume(TokenType type, const std::string& msg)
{
	if (check(type))
	{
		return advance();
	}
	throw error(peek(), msg);
}

ParseException Parser::error(const Token* token, const std::string& msg)
{
	Lox::error(token, msg);
	return ParseException();
}

Lexeme::Token* Parser::previous()
{
	return tokens[current - 1];
}

Lexeme::Token* Parser::peek()
{
	return tokens.at(this->current);
}

bool Parser::isAtEnd()
{
	return peek()->getType() == TokenType::END_OF_FILE;
}

Lexeme::Token* Parser::advance()
{
	if (!isAtEnd()) current++;
	return previous();
}

bool Parser::check(TokenType type)
{
	if (isAtEnd())
		return false;
	return peek()->getType() == type;
}

bool Parser::match(TokenType type)
{
	if (check(type))
	{
		advance();
		return true;
	}
	return false;
}

bool Parser::match(const std::vector<TokenType>& types)
{
	for (const TokenType& type : types)
	{
		if (check(type))
		{
			advance();
			return true;
		}
	}
	return false;
}

Stmt* Parser::statement()
{
	if (this->match(TokenType::PRINT))
		return this->printStatement();

	return this->expressionStatement();
}

/*
 * printStmt -> "print" expression ";" ;
 * */
Stmt* Parser::printStatement()
{
	Expr* value = this->expression();
	this->consume(TokenType::SEMICOLON, "Expect ';' after value.");

	return new Print(value);
}

/*
 * exprStmt -> expression ";" ;
 * */
Stmt* Parser::expressionStatement()
{
	Expr* value = this->expression();
	this->consume(TokenType::SEMICOLON, "Expect ';' after value.");

	return new Expression(value);
}

Stmt* Parser::declaration()
{
	try
	{
		if (this->match(TokenType::VAR))
			return varDeclaration();
		return statement();
	}
	catch (ParseException& pe)
	{
		this->synchronize();
		return nullptr;
	}
}

Stmt* Parser::varDeclaration()
{
	Token* name = this->consume(Lexeme::TokenType::IDENTIFIER, "Expect variable name.");
	Expr* initializer = nullptr;
	if (this->match(TokenType::EQUAL))
	{
		initializer = this->expression();
	}

	this->consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
	return new Var(name, initializer);
}

void Parser::synchronize()
{
	this->advance();

	while (!this->isAtEnd())
	{
		if (previous()->getType() == TokenType::SEMICOLON)
			return;
		switch (peek()->getType())
		{
			case TokenType::CLASS:
			case TokenType::FUN:
			case TokenType::VAR:
			case TokenType::FOR:
			case TokenType::IF:
			case TokenType::WHILE:
			case TokenType::PRINT:
			case TokenType::RETURN:
				return;
		}
		this->advance();
	}
}




