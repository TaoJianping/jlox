cmake_minimum_required(VERSION 3.14)
project(jlox)

set(CMAKE_CXX_STANDARD 17)

add_executable(jlox main.cpp Lox.cpp Lox.h Enum.h Token.cpp Token.h Scanner.cpp Scanner.h TestLox.cpp TestLox.h Config.h Expr.cpp Expr.h tool/GenerateAst.cpp tool/GenerateAst.h Parser.cpp Parser.h Visitor.cpp Visitor.h)