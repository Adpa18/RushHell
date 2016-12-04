#include <iostream>
#include <boost/bind.hpp>
#include <cassert>
#include "Function.hpp"

void zerofunction1(void)
{
    std::cout << "zero func1" << std::endl;
}
void zerofunction2(void)
{
    std::cout << "zero func2" << std::endl;
}

int addition(int a, int b)
{
    return a + b;
}

void unitTestFunctor()
{
    std::cout << "\033[1;33m" << "Start Tests Functor tests :" << "\033[0m" << std::endl << std::endl;

    Function<void()> f = &zerofunction1;

    f();
    std::cout << "\t\033[1;34m" << "test " << 1 << "/" << 6 << " passed" << "\033[0m" << std::endl;

    f = &zerofunction2;
    f();
    std::cout << "\t\033[1;34m" << "test " << 2 << "/" << 6 << " passed" << "\033[0m" << std::endl;

    Function<int()>f1 = boost::bind(&addition, 1, 2);
    assert(f1() == 3);
    std::cout << "\t\033[1;34m" << "test " << 3 << "/" << 6 << " passed" << "\033[0m" << std::endl;

    f1 = boost::bind(&addition, 4, 2);
    assert(f1() == 6);
    std::cout << "\t\033[1;34m" << "test " << 4 << "/" << 6 << " passed" << "\033[0m" << std::endl;

    Function<int(int, int)>f2 = &addition;
    assert(f2(22, 20) == 42);
    std::cout << "\t\033[1;34m" << "test " << 5 << "/" << 6 << " passed" << "\033[0m" << std::endl;

    Function<int(int)>f3 = boost::bind(&addition, _1, 20);
    assert(f3(22) == 42);
    std::cout << "\t\033[1;34m" << "test " << 6 << "/" << 6 << " passed" << "\033[0m" << std::endl;

    std::cout << "\033[1;32m" << "Tests Functor OK" << "\033[0m" << std::endl << std::endl;
}

int main() {
    unitTestFunctor();
    return 0;
}