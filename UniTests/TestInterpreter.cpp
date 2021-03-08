//
// Created by tao on 2021/3/2.
//

#include "TestInterpreter.h"
#include "gtest/gtest.h"
#include "Lox.h"

TEST(testInterpreter, test1) {
	auto lox = Lox();
	lox.runFile("../../resource/test/test.txt");
}

TEST(testInterpreter, testIF) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testIf.txt");
}