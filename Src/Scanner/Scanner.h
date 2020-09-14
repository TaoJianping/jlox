//
// Created by taojianping on 2019/8/19.
//

#ifndef JLOX_SCANNER_H
#define JLOX_SCANNER_H
#include <iostream>
#include <vector>
#include <variant>
#include <any>
#include "Token.h"

using namespace std;

class Scanner {
private:
    string source;
    vector<Token *> tokens;
    int line;
    int start;

    int current;
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType tt);
    void addToken(TokenType tt, string literal);
    void addToken(TokenType tt, double literal);
    void addToken(TokenType tt, nullptr_t literal);
    bool match(char c);
    char peek();
    void readString();
    void readNumber();
    char peekNext();
    void identifier();
public:
    explicit Scanner(string const &s) {
        source = s;
        line = 1;
        start = 0;
        current = 0;
    }

    const vector<Token *> & scanTokens();
};


#endif //JLOX_SCANNER_H
