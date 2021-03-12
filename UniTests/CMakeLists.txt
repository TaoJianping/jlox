cmake_minimum_required(VERSION 3.14)
SET(CMAKE_TOOLCHAIN_FILE "/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake")


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")


project(jloxTests)

# install google test
message(STATUS "Start Install GoogleTest")
find_package(GTest CONFIG REQUIRED)
if (GTest_FOUND)
    message(Fount GTest !)
endif ()

# install google log
message(STATUS "Start Install glog")
find_package(glog CONFIG REQUIRED)
if (glog_FOUND)
    message(Fount glog !)
endif ()


include_directories(../Src)
#add_subdirectory(../Src SourceDir)



set(
        Headers
        TestBasic.h
        TestScanner.h
)

set(
        Sources
        TestBasic.cpp
        TestScanner.cpp
)


set(
        ExecutableFile
        ../Src/Scanner.cpp
        ../Src/Token.cpp
        ../Src/Lox.cpp
        ../Src/Expr.cpp
        ../Src/AstPrinter.cpp
        ../Src/AstPrinter.h
        TestTools.cpp
        TestTools.h
        ../Src/Parser.h
        ../Src/Parser.cpp
        ../Src/Interpreter.cpp ../Src/Interpreter.h ../Src/RunTimeException.cpp ../Src/RunTimeException.h TestInterpreter.cpp TestInterpreter.h ../Src/Stmt.cpp ../Src/Stmt.h ../Src/Environment.cpp ../Src/Environment.h ../Src/LoxCallable.cpp ../Src/LoxCallable.h ../Src/Type.h ../Src/LoxFunction.cpp ../Src/LoxFunction.h ../Src/ReturnStatement.h)


ADD_EXECUTABLE(LoxTest ${Headers} ${Sources} ${ExecutableFile})
target_link_libraries(LoxTest GTest::gtest GTest::gtest_main)