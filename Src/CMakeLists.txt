cmake_minimum_required(VERSION 3.14)
SET(CMAKE_TOOLCHAIN_FILE "/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake")


project(jlox)


add_subdirectory(Scanner)


add_executable(jlox main.cpp Lox.cpp Lox.h)
TARGET_LINK_LIBRARIES(jlox Scanner)