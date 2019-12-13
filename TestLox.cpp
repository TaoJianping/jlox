//
// Created by taojianping on 2019/9/3.
//

#include "TestLox.h"
#include "Lox.h"

void TestLox::run() {
    std::string path = R"(C:\Users\taojianping\Documents\PeronalProjects\jlox\resource\test\test.txt)";
    Lox().runFile(path);
}
