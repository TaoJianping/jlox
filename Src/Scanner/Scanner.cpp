//
// Created by taojianping on 2019/8/19.
//

#include "Scanner.h"
#include "../Common/Enum.h"
#include "../Lox.h"
#include "../../Config.h"
#include <utility>
#include <vector>


const vector<Token*> & Scanner::scanTokens()  {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    auto et = new Token(TokenType::END_OF_FILE, "", "", line);
    tokens.push_back(et);
    return tokens;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

void Scanner::scanToken() {
    auto c = advance();
    switch (c) {
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;
        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case '.':
            addToken(TokenType::DOT);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case '*':
            addToken(TokenType::STAR);
            break;
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case ' ':
            break;
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            line++;
            break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        case '"':
            readString();
            break;
        default:
            if (isdigit(c)) {
                readNumber();
            } else if (isalpha(c)) {
                identifier();
            }
            // Lox::error(line, "Unexpected character.");
            break;
    }
}

char Scanner::advance() {
    char ret = source.at(current);
    current++;
    return ret;
}

void Scanner::addToken(TokenType tt) {
    addToken(tt, nullptr);
}

void Scanner::addToken(TokenType type, string literal) {
    // Todo
    string text = source.substr(start, (current - start));
    auto t = new Token(type, text, literal, line);
    tokens.push_back(t);
}

void Scanner::addToken(TokenType type, nullptr_t aNullptr) {
    string text = source.substr(start, (current - start));
    auto t = new Token(type, text, "nil", line);
    tokens.push_back(t);
}

bool Scanner::match(char expected) {
    if (expected != source.at(current)) {
        return false;
    }
    current++;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source.at(current);
}

void Scanner::readString() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    // error handling
    if (isAtEnd()) {
        std::cout << "Unterminated string." << std::endl;
        return;
    }

    // The closing ".
    advance();

    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, current - start - 1 - 1);
    addToken(TokenType::STRING, value);
}

void Scanner::readNumber() {
    while (isdigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isdigit(peekNext())) {
        // Consume the "."
        advance();
        while (isdigit(peek())) advance();
    }

    std::string value = source.substr(start, current);
    addToken(TokenType::NUMBER, value);
}

char Scanner::peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source.at(current + 1);
}

void Scanner::identifier() {
    while (isalnum(peek()) && peek() != ' ') advance();

    string text = source.substr(start, current);
    TokenType t;
    if (KEYWORDS.count(text) == 0) {
        t = TokenType::IDENTIFIER;
    } else {
        t = KEYWORDS.at(text);
    }
    addToken(t);
}
