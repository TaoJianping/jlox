//
// Created by taojianping on 2019/9/11.
//

#include "Parser.h"

#include <utility>

//  expression     → equality ;
//  equality       → comparison ( ( "!=" | "==" ) comparison )* ;
//  comparison     → addition ( ( ">" | ">=" | "<" | "<=" ) addition )* ;
//  addition       → multiplication ( ( "-" | "+" ) multiplication )* ;
//  multiplication → unary ( ( "/" | "*" ) unary )* ;
//  unary          → ( "!" | "-" ) unary | primary ;
//  primary        → NUMBER | STRING | "false" | "true" | "nil" | "(" expression ")";


Expr *Parser::expression() {
    return equality();
}


Token *Parser::previous() {
    return tokens[current - 1];
}

Token *Parser::peek() {
    return tokens[current];
}

bool Parser::isAtEnd() {
    return peek()->type == TokenType::END_OF_FILE;
}

Token *Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek()->type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::match(const vector<TokenType> & types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

// equality → comparison ( ( "!=" | "==" ) comparison )* ;
Expr *Parser::equality() {
    Expr *expr = comparison();

    auto ts = std::vector<TokenType>();
    ts.push_back(TokenType::BANG_EQUAL);
    ts.push_back(TokenType::EQUAL_EQUAL);
    while (match(ts)) {
        Token &oper = *previous();
        Expr *right = comparison();
        expr = static_cast<Expr*>(new Binary(expr, oper, right));
    }

    return expr;
}

// comparison → addition ( ( ">" | ">=" | "<" | "<=" ) addition )* ;
Expr *Parser::comparison() {
    Expr* expr = addition();

    auto ts = std::vector<TokenType>();
    ts.push_back(TokenType::GREATER);
    ts.push_back(TokenType::GREATER_EQUAL);
    ts.push_back(TokenType::LESS);
    ts.push_back(TokenType::LESS_EQUAL);

    while (match(ts)) {
        Token oper = *previous();
        Expr* right = addition();
        expr = (Expr *) new Binary(expr, oper, right);
    }

    return expr;
}

// addition → multiplication ( ( "-" | "+" ) multiplication )* ;
Expr *Parser::addition() {
    Expr* expr = multiplication();

    auto ts = std::vector<TokenType>();
    ts.push_back(TokenType::MINUS);
    ts.push_back(TokenType::PLUS);

    while (match(ts)) {
        Token oper = *previous();
        Expr* right = multiplication();
        expr = (Expr *) new Binary(expr, oper, right);
    }

    return expr;
}

// unary (("/" | "*" ) unary)* ;
Expr *Parser::multiplication() {
    Expr* expr = unary();

    auto ts = std::vector<TokenType>();
    ts.push_back(TokenType::SLASH);
    ts.push_back(TokenType::STAR);

    while (match(ts)) {
        Token oper = *previous();
        Expr* right = unary();
        expr = (Expr *) new Binary(expr, oper, right);
    }

    return expr;
}

//unary → ( "!" | "-" ) unary | primary ;
Expr *Parser::unary() {
    auto ts = std::vector<TokenType>();
    ts.push_back(TokenType::BANG);
    ts.push_back(TokenType::MINUS);

    Expr * expr;
    while (match(ts)) {
        Token oper = *previous();
        Expr* right = unary();
        expr = (Expr *) new Unary(oper, right);
        return expr;
    }

    return primary();
}

// primary → NUMBER | STRING | "false" | "true" | "nil" | "(" expression ")" ;
Expr *Parser::primary() {

    auto ts = std::vector<TokenType>();
    ts.push_back(TokenType::FALSE);
    ts.push_back(TokenType::TRUE);
    ts.push_back(TokenType::NIL);
    ts.push_back(TokenType::STRING);
    ts.push_back(TokenType::NUMBER);

    if (match(ts)) {
        auto ret = new Literal(*previous());
        return (Expr *) ret;
    }

    if (match(TokenType::LEFT_PAREN)) {
        Expr* expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return (Expr *) new Grouping(expr);
    }

    throw std::exception();
}

Token *Parser::consume(TokenType type, const std::string& msg) {
    if (check(type)) {
        return advance();
    }
    return nullptr;
    throw error(peek(), msg);
}



