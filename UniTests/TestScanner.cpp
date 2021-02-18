//
// Created by tao on 2020/9/15.
//

#include "TestScanner.h"
#include "gtest/gtest.h"
#include "Scanner.h"


TEST(testScanner, test1) {
    const string str = "123 == 12;";
    auto scanner = Scanner(str);
    auto ts = scanner.scanTokens();

    for (const auto t : ts)
    {
        std::cout << t << std::endl;
    }
}