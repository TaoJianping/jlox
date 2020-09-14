//
// Created by taojianping on 2019/8/17.
//

#include "Lox.h"
#include "Scanner/Scanner.h"
// #include "../Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool Lox::hasError = false;

int Lox::main(int argc,char *argv[]) {
    if (argc > 1) {
        std::cout << "Usage: jlox [script]";
        exit(64);
    } else if (argc == 1) {
        runFile(argv[0]);
    } else {
        runPrompt();
    }

    return 0;
}

void Lox::runFile(string const & path) {
    std::ifstream file;
    file.open(path);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string fileContent(buffer.str());
        run(fileContent);
    }
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
    auto scanner = Scanner(source);
    auto tokens = scanner.scanTokens();
//    auto parser = new Parser(tokens);
//    Expr* expr = parser->parse();
    for (auto t: tokens) {
        t->toString();
    }
    if (Lox::hasError) {
        exit(65);
    }
}
