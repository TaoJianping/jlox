//
// Created by taojianping on 2019/8/19.
//

#include "Scanner.h"
#include "Token.h"
#include "Lox.h"
#include <utility>
#include <vector>


vector<Lexeme::Token*> Lexer::Scanner::scanTokens()
{
	while (!isAtEnd())
	{
		start = current;
		scanToken();
	}
	auto et = new Token(TokenType::END_OF_FILE, "END_OF_FILE", "END_OF_FILE", line);
	tokens.push_back(et);
	return tokens;
}

bool Lexer::Scanner::isAtEnd()
{
	return current >= source.length();
}

void Lexer::Scanner::scanToken()
{
	auto c = advance();
	switch (c)
	{
	case '(':
		addToken(TokenType::LEFT_PAREN);
		break;
	case ')':
		addToken(TokenType::RIGHT_PAREN);
		break;
	case '{':
		addToken(TokenType::LEFT_BRACE);
		break;
	case '}':
		addToken(TokenType::RIGHT_BRACE);
		break;
	case ',':
		addToken(TokenType::COMMA);
		break;
	case '.':
		addToken(TokenType::DOT);
		break;
	case '-':
		addToken(TokenType::MINUS);
		break;
	case '+':
		addToken(TokenType::PLUS);
		break;
	case ';':
		addToken(TokenType::SEMICOLON);
		break;
	case '*':
		addToken(TokenType::STAR);
		break;
	case '!':
		addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
		break;
	case '=':
		addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
		break;
	case '<':
		addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
		break;
	case '>':
		addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
		break;
	case ' ':
		break;
	case '\r':
	case '\t':
		// Ignore whitespace.
		break;
	case '\n':
		line++;
		break;
	case '/':
		if (match('/'))
		{
			while (peek() != '\n' && !isAtEnd()) advance();
		}
		else
		{
			addToken(TokenType::SLASH);
		}
		break;
	case '"':
		readString();
		break;
	default:
		if (isdigit(c))
		{
			readNumber();
		}
		else if (isalpha(c))
		{
			identifier();
		}
		else
		{
			Lox::error(line, "Unexpected character.");
		}
		break;
	}
}

char Lexer::Scanner::advance()
{
	char ret = source.at(current);
	current++;
	return ret;
}

void Lexer::Scanner::addToken(TokenType tt)
{
	if (tt == TokenType::TRUE || tt == TokenType::FALSE)
	{
		addToken(tt, tt == TokenType::TRUE);
	}
	else
	{
		addToken(tt, nullptr);
	}
}

void Lexer::Scanner::addToken(Lexeme::TokenType type, bool literal)
{
	string text = source.substr(start, (current - start));
	auto t = new Token(type, text, literal, line);
	tokens.push_back(t);
}

void Lexer::Scanner::addToken(TokenType type, string literal)
{
	string text = source.substr(start, (current - start));
	auto t = new Token(type, text, literal, line);
	tokens.push_back(t);
}

void Lexer::Scanner::addToken(TokenType type, nullptr_t nil)
{
	string text = source.substr(start, (current - start));
	auto t = new Token(type, text, std::monostate(), line);
	tokens.push_back(t);
}


void Lexer::Scanner::addToken(TokenType type, double number)
{
	string text = source.substr(start, (current - start));
	auto t = new Token(type, text, number, line);
	tokens.push_back(t);
}


bool Lexer::Scanner::match(char expected)
{
	if (isAtEnd())
		return false;
	if (expected != source.at(current))
		return false;

	current++;
	return true;
}

char Lexer::Scanner::peek()
{
	if (isAtEnd()) return '\0';
	return source.at(current);
}

void Lexer::Scanner::readString()
{
	while (peek() != '"' && !isAtEnd())
	{
		if (peek() == '\n') line++;
		advance();
	}

	// error handling
	if (isAtEnd())
	{
		Lox::error(line, "Unterminated string.");
//        std::cout << "Unterminated string." << std::endl;
		return;
	}

	// The closing ".
	advance();

	// Trim the surrounding quotes.
	std::string value = source.substr(start + 1, current - start - 1 - 1);
	addToken(TokenType::STRING, value);
}

void Lexer::Scanner::readNumber()
{
	while (isdigit(peek())) advance();

	// Look for a fractional part.
	if (peek() == '.' && isdigit(peekNext()))
	{
		// Consume the "."
		advance();
		while (isdigit(peek())) advance();
	}

	std::string value = source.substr(start, current);
	double number = stod(value);
	addToken(TokenType::NUMBER, number);
}

char Lexer::Scanner::peekNext()
{
	if (current + 1 >= source.length()) return '\0';
	return source.at(current + 1);
}

void Lexer::Scanner::identifier()
{
	while ((isalnum(peek()) && peek() != ' '))
		advance();

	string text = source.substr(start, current - start);
	TokenType t;
	if (KEYWORDS.count(text) == 0)
	{
		t = TokenType::IDENTIFIER;
	}
	else
	{
		t = KEYWORDS.at(text);
	}
	addToken(t);
}

