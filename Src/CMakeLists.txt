cmake_minimum_required(VERSION 3.14)
SET(CMAKE_TOOLCHAIN_FILE "/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake")


project(jlox)

SET(HEADER Token.h)
SET(SOURCE Token.cpp)


add_executable(jlox main.cpp Lox.cpp Lox.h Token.h Token.cpp Scanner.cpp Scanner.h)
TARGET_LINK_LIBRARIES(jlox)