//
// Created by tao on 2021/2/24.
//

#include "TestTools.h"
#include "../Src/AstPrinter.h"
#include "gtest/gtest.h"


TEST(testAstPrinterCase, test1) {
	using namespace Lexeme;
	double n = 123;
	double n1 = 45.67;
	auto visitor = new AstPrinter();

	auto minusToken = new Lexeme::Token(Lexeme::TokenType::MINUS, "-", "", 1);


//	Expr* expression = new Binary(
//			new Unary(minusToken,
//					new Literal(new Lexeme::Token(Lexeme::TokenType::NUMBER, "123", n, 1))
//				),
//			new Token(TokenType::STAR, "*", "", 1),
//			new Grouping(new Literal(new Lexeme::Token(Lexeme::TokenType::NUMBER, "45.67", n1, 1)))
//
//		);
//	std::cout << visitor->print(*expression) << std::endl;
}

