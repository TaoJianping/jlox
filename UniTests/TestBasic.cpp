//
// Created by tao on 2020/9/12.
//

#include "TestBasic.h"
#include "gtest/gtest.h"
#include "../Src/Lox.h"


TEST(testString, test1) {
    auto lox = new Lox();
    lox->runFile("../resource/test/test.txt");
}
