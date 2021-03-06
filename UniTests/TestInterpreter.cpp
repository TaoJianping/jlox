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

TEST(testInterpreter, testLogical) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testLogical.txt");
}


TEST(testInterpreter, testFor) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testFor.txt");
}

TEST(testInterpreter, testFun) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testFunction.txt");
}

TEST(testInterpreter, testReturn) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testReturn.txt");
}

TEST(testInterpreter, testClosure) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testClosure.txt");
}

TEST(testInterpreter, testResolve) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testResolve.txt");
}

TEST(testInterpreter, testClass1) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testClass1.txt");
}

TEST(testInterpreter, testClass2) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testClass2.txt");
}

TEST(testInterpreter, testClass3) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testClass3.txt");
}

TEST(testInterpreter, testClass4) {
	auto lox = Lox();
	lox.runFile("../../resource/test/testClass4.txt");
}