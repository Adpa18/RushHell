#include <iostream>
#include "Function.hpp"

int zerofunction()
{
    return 1;
}

int main() {
    Function<int()> f = &zerofunction;

    f();
    f = &zerofunction;
    f();
    return 0;
}