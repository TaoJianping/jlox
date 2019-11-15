//
// Created by taojianping on 2019/8/17.
//

#ifndef JLOX_LOX_H
#define JLOX_LOX_H
#include <iostream>
using namespace std;
#include "Token.h"

class Lox {
public:
    void main(int argc,char *argv[]);
    void runFile(string const & path);
    void error(const Token& token, std::string);
    void runPrompt();
    static bool hasError;
private:
    static void report(int, string const &where, string const &messages);
    void run(string const & source);
};


#endif //JLOX_LOX_H
