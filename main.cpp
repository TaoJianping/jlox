#include <iostream>
#include "Lox.h"
#include "fstream"
#include "Token.h"
#include "TestLox.h"
#include <vector>

using namespace std;

int main(int argc,char *argv[]) {
    // TestLox().run();
    const int n = 100;
    int *p = const_cast<int*>(&n);
    long b = const_cast<long>(n);
    *p = 234;
    cout<<"n = "<<n<<endl;
    cout<<"*p = "<<*p<<endl;
    return 0;
}