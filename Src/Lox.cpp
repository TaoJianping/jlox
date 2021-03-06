//
// Created by taojianping on 2019/8/17.
//

#include "Lox.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Resolver.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool Lox::hasError = false;
bool Lox::hadRuntimeError = false;

int Lox::main(int argc, char* argv[])
{
	if (argc > 1)
	{
		std::cout << "Usage: jlox [script]";
		exit(64);
	}
	else if (argc == 1)
	{
		runFile(argv[0]);
	}
	else
	{
		runPrompt();
	}

	return 0;
}

void Lox::runFile(string const& path)
{
	std::ifstream file;
	file.open(path);
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string fileContent(buffer.str());
		run(fileContent);
	}
	else
	{
		std::cout << "Not FOUNT FILE!!!" << std::endl;
	}
}

void Lox::error(int line, std::string message)
{
	Lox::report(line, "", message);
}

void Lox::report(int line, string const& where, string const& messages)
{
	std::cout << "[line " << line << "] Error" + where + ": " + messages << endl;
	Lox::hasError = true;
}

/*
 * 教程里面是直接在终端运行，类似于直接打开Python，跳出来终端
 * 我就暂时略过
 * */
void Lox::runPrompt()
{
	std::cout << "> " << std::endl;
	std::string test = "var language = \"lox\";";
	run(test);
}

void Lox::run(string const& source)
{
	auto scanner = Lexer::Scanner(source);
	auto tokens = scanner.scanTokens();
	auto parser = new Parser(tokens);
	auto statements = parser->parse();

	if (Lox::hasError)
	{
		exit(65);
	}

	auto interpreter = Interpreter();
	auto resolver = new Resolver(&interpreter);
	resolver->resolve(statements);

	if (Lox::hasError)
	{
		exit(65);
	}

	interpreter.interpret(statements);

	if (Lox::hadRuntimeError)
	{
		exit(70);
	}
}

void Lox::error(const Lexeme::Token* token, const std::string& message)
{
	if (token->getType() == Lexeme::TokenType::END_OF_FILE)
	{
		Lox::report(token->getLine(), " at end", message);
	}
	else
	{
		Lox::report(token->getLine(), " at" + token->getLexeme(), message);
	}
}

void Lox::runtimeError(RunTimeException exception)
{
	std::cout << exception.what() << std::endl;
	std::cout << "[Line: " << exception.getLine() << "]" << std::endl;
	Lox::hadRuntimeError = true;
}
