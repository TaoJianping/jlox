//
// Created by taojianping on 2019/8/17.
//

#ifndef JLOX_LOX_H
#define JLOX_LOX_H

#include <iostream>
#include "Token.h"

using namespace std;


class Lox
{
public:
	int main(int argc, char* argv[]);

	void runFile(string const& path);

	static void error(int line, std::string);

	void runPrompt();

	static bool hasError;
private:
	static void report(int, string const& where, string const& messages);

	void run(string const& source);
};


#endif //JLOX_LOX_H
