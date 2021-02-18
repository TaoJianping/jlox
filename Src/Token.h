//
// Created by taojianping on 2019/8/19.
//

#ifndef JLOX_TOKEN_H
#define JLOX_TOKEN_H

#include <iostream>
#include <utility>

namespace Lexeme {
	enum class TokenType {
		// Single-character tokens.
		LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
		COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

		// One or two character tokens.
		BANG, BANG_EQUAL,
		EQUAL, EQUAL_EQUAL,
		GREATER, GREATER_EQUAL,
		LESS, LESS_EQUAL,

		// Literals.
		IDENTIFIER, STRING, NUMBER,

		// Keywords.
		AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
		PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

		END_OF_FILE
	};

	class Token {
	public:
		Token(TokenType t, std::string lexeme, std::string ll, int l);

		~Token() {
			std::cout << "Fuck~~~\n";
		}

		friend std::ostream &operator<<( std::ostream &output, const Token &token )
		{
			std::string typeStr;
			switch (token.type) {
			case TokenType::LEFT_PAREN:
				typeStr = "LEFT_PAREN";
				break;
			default:
				break;
			}

//        output << "TokenType : " << token.lexeme;
			output << "TokenLexeme : " << token.lexeme;
			return output;
		}

		std::string toString();


	private:
		int line;
		std::string lexeme;
		std::string literal;
		TokenType type;
	};
}






#endif //JLOX_TOKEN_H
