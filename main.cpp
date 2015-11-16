#include <iostream>

#include "BigInt.h"
using namespace std;

int main() {
    BigInt myint1 = "1543215486541318664684843518410051016840464156035835443435345345345435345345345";
    BigInt myint2 = 156341300544608LL;

    myint1 = myint2 + myint2 + myint1 - 3;
    std::cout << myint1 << std::endl;

    return 0;
}