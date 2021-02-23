//
// Created by tao on 2020/9/15.
//

#include "TestScanner.h"
#include "gtest/gtest.h"
#include "../Src/Scanner.h"
//#include "../Src/Token.h"
//#include "Scanner.h"


TEST(testScanner, test1) {
	using namespace Lexeme;
    const std::string str = "var a = 123;";
    auto scanner = Lexer::Scanner(str);
    auto ts = scanner.scanTokens();

    for (const auto t : ts)
    {
    	if (t->getType() == TokenType::NUMBER) {
        	std::cout << t << std::endl;
    	}
    	if (t->getType() == TokenType::STRING) {

    	}
    }
}