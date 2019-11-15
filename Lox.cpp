//
// Created by taojianping on 2019/8/17.
//

#include "Lox.h"
#include "Scanner.h"
#include <iostream>
#include <fstream>

using namespace std;

bool Lox::hasError = false;

void Lox::main(int argc,char *argv[]) {
    if (argc > 1) {
        std::cout << "Usage: jlox [script]";
        exit(64);
    } else if (argc == 1) {
        runFile(argv[0]);
    } else {
        runPrompt();
    }
}

void Lox::runFile(string const & path) {
    std::ifstream t(path);
    std::string fileContent((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    run(fileContent);
}

void Lox::error(const Token& token, std::string message) {
    if (token.type == TokenType::END_OF_FILE) {
        Lox::report(token.line, " at end", message);
    } else {
        Lox::report(token.line, " at '" + token.lexeme + "'", message);
    }
}

void Lox::report(int line, string const& where  , string const& messages) {
    std::cout <<  "[line " <<  line << "] Error" + where + ": " + messages << endl;
    Lox::hasError = true;
}

void Lox::runPrompt() {
    std::cout << "> " << std::endl;
    std::string test = "var language = \"lox\";";
    run(test);
}

void Lox::run(string const &source) {
    auto scanner = new Scanner(source);
    auto tokens = scanner->scanTokens();
    for (auto t: tokens) {
        t->toString();
    }
    if (Lox::hasError) {
        exit(65);
    }
}
