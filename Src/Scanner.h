//
// Created by taojianping on 2019/8/19.
//

#ifndef JLOX_SCANNER_H
#define JLOX_SCANNER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Token.h"

namespace Lexer
{
	using namespace Lexeme;

	const std::unordered_map<std::string, TokenType> KEYWORDS = {
			{ "and",    TokenType::AND },
			{ "class",  TokenType::CLASS },
			{ "else",   TokenType::ELSE },
			{ "false",  TokenType::FALSE },
			{ "for",    TokenType::FOR },
			{ "fun",    TokenType::FUN },
			{ "if",     TokenType::IF },
			{ "nil",    TokenType::NIL },
			{ "or",     TokenType::OR },
			{ "print",  TokenType::PRINT },
			{ "return", TokenType::RETURN },
			{ "super",  TokenType::SUPER },
			{ "this",   TokenType::THIS },
			{ "true",   TokenType::TRUE },
			{ "var",    TokenType::VAR },
			{ "while",  TokenType::WHILE },
	};


	class Scanner
	{
	private:
		std::string source;
		std::vector<Token*> tokens;
		int line;
		int start;

		int current;

		bool isAtEnd();

		void scanToken();

		char advance();

		void addToken(TokenType tt);

		void addToken(TokenType tt, std::string literal);

		void addToken(TokenType tt, double literal);

		void addToken(TokenType tt, std::nullptr_t literal);

		void addToken(TokenType tt, bool literal);

		bool match(char c);

		char peek();

		void readString();

		void readNumber();

		char peekNext();

		void identifier();

	public:
		explicit Scanner(std::string const& s)
		{
			source = s;
			line = 1;
			start = 0;
			current = 0;
		}

		std::vector<Token*> scanTokens();
	};

}


#endif //JLOX_SCANNER_H
