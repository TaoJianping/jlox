//
// Created by taojianping on 2019/9/11.
//

#include "Parser.h"

#include "Lox.h"
#include <utility>


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
//	return equality();
	return assignment();
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

	return this->call();
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
	if (this->match(TokenType::FOR))
		return this->forStatement();

	if (this->match(TokenType::IF))
		return this->ifStatement();

	if (this->match(TokenType::RETURN))
		return this->returnStatement();

	if (this->match(TokenType::PRINT))
		return this->printStatement();

	if (this->match(TokenType::WHILE))
		return this->whileStatement();

	if (this->match(TokenType::LEFT_BRACE))
		return new Block(block());

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
		if (this->match(TokenType::CLASS))
			return this->classDeclaration();

		if (this->match(TokenType::FUN))
			return this->function("function");

		if (this->match(TokenType::VAR))
			return this->varDeclaration();

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

Expr* Parser::assignment()
{
	Expr* expr = this->_or();
	if (this->match(TokenType::EQUAL))
	{
		Token* equals = this->previous();
		Expr* value = this->assignment();

		auto castExpr = dynamic_cast<Variable*>(expr);
		if (castExpr != nullptr)
		{
			Token* name = castExpr->name;
			return new Assign(name, value);
		}
		else if (auto getExpr = dynamic_cast<Get*>(expr); getExpr != nullptr)
		{
			return new Set(getExpr->object, getExpr->name, value);
		}


		throw this->error(equals, "Invalid assignment target.");
	}

	return expr;
}

vector<Stmt*> Parser::block()
{
	vector<Stmt*> statements;

	while (!this->check(TokenType::RIGHT_BRACE) && !this->isAtEnd())
	{
		statements.push_back(this->declaration());
	}

	this->consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
	return statements;
}

Stmt* Parser::ifStatement()
{
	this->consume(TokenType::LEFT_PAREN, "Expect '(' after 'if'.");
	Expr* condition = this->expression();
	this->consume(TokenType::RIGHT_PAREN, "Expect '(' after 'if'.");

	Stmt* thenBranch = this->statement();
	Stmt* elseBranch = nullptr;
	if (this->match(TokenType::ELSE))
	{
		elseBranch = this->statement();
	}

	return new If(condition, thenBranch, elseBranch);
}

Expr* Parser::_or()
{
	Expr* expr = this->_and();

	while (this->match(TokenType::OR))
	{
		Token* _operator = this->previous();
		Expr* right = this->_and();
		expr = new Logical(expr, _operator, right);
	}

	return expr;
}

Expr* Parser::_and()
{
	Expr* expr = this->equality();

	while (this->match(TokenType::AND))
	{
		Token* _operator = this->previous();
		Expr* right = this->equality();
		expr = new Logical(expr, _operator, right);
	}

	return expr;
}

Stmt* Parser::whileStatement()
{
	this->consume(TokenType::LEFT_PAREN, "Expect '(' after 'while'.");
	Expr* condition = this->expression();
	this->consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");
	Stmt* body = this->statement();

	return new While(condition, body);
}

Stmt* Parser::forStatement()
{
	this->consume(TokenType::LEFT_PAREN, "Expect '(' after 'for'.");
	Stmt* initializer;
	if (this->match(TokenType::SEMICOLON))
	{
		initializer = nullptr;
	}
	else if (this->match(TokenType::VAR))
	{
		initializer = this->varDeclaration();
	}
	else
	{
		initializer = this->expressionStatement();
	}

	Expr* condition = nullptr;
	if (!this->check(TokenType::SEMICOLON))
	{
		condition = this->expression();
	}
	this->consume(TokenType::SEMICOLON, "Expect ';' after loop condition.");

	Expr* increment = nullptr;
	if (!this->check(TokenType::RIGHT_PAREN))
	{
		increment = this->expression();
	}
	this->consume(TokenType::RIGHT_PAREN, "Expect ')' after for clauses.");

	Stmt* body = this->statement();
	if (increment != nullptr)
	{
		body = new Block({ body, new Expression(increment) });
	}

	if (condition == nullptr)
		condition = new Literal(new Token(TokenType::TRUE, "true", true, -1));

	body = new While(condition, body);

	if (initializer != nullptr)
	{
		body = new Block({ initializer, body });
	}

	return body;
}

Expr* Parser::call()
{
	Expr* expr = this->primary();

	while (true)
	{
		if (this->match(TokenType::LEFT_PAREN))
		{
			expr = this->finishCall(expr);
		}
		else if (this->match(TokenType::DOT))
		{
			auto name = this->consume(TokenType::IDENTIFIER, "Expect property name after '.'.");
			expr = new Get(expr, name);
		}
		else
		{
			break;
		}
	}

	return expr;
}

Expr* Parser::finishCall(Expr* callee)
{
	vector<Expr*> arguments;

	if (!this->check(TokenType::RIGHT_PAREN))
	{
		do
		{
			if (arguments.size() >= 255)
			{
				this->error(this->peek(), "Can't have more than 255 arguments.");
			}
			arguments.push_back(this->expression());
		} while (this->match(TokenType::COMMA));
	}

	Token* paren = this->consume(TokenType::RIGHT_PAREN, "Expect ')' after arguments.");

	return new Call(callee, paren, std::move(arguments));
}

Function* Parser::function(string kind)
{
	Token* name = this->consume(TokenType::IDENTIFIER, "Expect" + kind + " name.");
	this->consume(TokenType::LEFT_PAREN, "Expect '(' after " + kind + " name.");

	vector<Token*> parameters{};
	if (!this->check(TokenType::RIGHT_PAREN))
	{
		do
		{
			if (parameters.size() >= 255)
				this->error(this->peek(), "Can't have more than 255 parameters.");
			parameters.push_back(this->consume(TokenType::IDENTIFIER, "Expect parameter name."));
		} while (this->match(TokenType::COMMA));
	}
	this->consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");

	this->consume(TokenType::LEFT_BRACE, "Expect '{' before " + kind + " body.");
	vector<Stmt*> body = this->block();

	return new Function(name, parameters, body);
}

Stmt* Parser::returnStatement()
{
	Token* keyword = this->previous();
	Expr* value = nullptr;
	if (!this->check(TokenType::SEMICOLON))
	{
		value = expression();
	}
	this->consume(TokenType::SEMICOLON, "Expect ';' after return value.");
	return new Return(keyword, value);
}

Stmt* Parser::classDeclaration()
{
	auto name = this->consume(Lexeme::TokenType::IDENTIFIER, "Expect class name.");
	this->consume(Lexeme::TokenType::LEFT_BRACE, "Expect '{' before class body.");

	vector<Function*> methods{};
	while (!this->check(Lexeme::TokenType::RIGHT_BRACE) && !this->isAtEnd())
	{
		methods.push_back(this->function("method"));
	}

	this->consume(Lexeme::TokenType::RIGHT_BRACE, "Expect '}' after class body.");
	return new Class(name, nullptr, methods);
}




