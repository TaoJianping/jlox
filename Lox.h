//
// Created by taojianping on 2019/8/17.
//

#ifndef JLOX_LOX_H
#define JLOX_LOX_H
#include <iostream>
using namespace std;

class Lox {
public:
    void main(int argc,char *argv[]);
    void runFile(string const & path);
    void error(int, char*);
    void runPrompt();
private:
    bool hasError;
    void report(int, string const &where, string const &messages);
    void run(string const & source);
};


#endif //JLOX_LOX_H
