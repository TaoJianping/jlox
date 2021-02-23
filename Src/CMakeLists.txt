cmake_minimum_required(VERSION 3.14)
SET(CMAKE_TOOLCHAIN_FILE "/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake")


project(jlox)

SET(HEADER Token.h)
SET(SOURCE Token.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")



add_executable(jlox main.cpp Lox.cpp Lox.h Token.h Token.cpp Scanner.cpp Scanner.h Expr.h Expr.cpp)
TARGET_LINK_LIBRARIES(jlox)