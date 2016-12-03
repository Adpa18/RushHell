#include <iostream>
#include "FunctionSignature.hpp"

int zerofunction()
{
    return 0;
}

int onefunction(const std::string& str)
{
    std::cout << str << std::endl;
    return 0;
}

int twofunction(const std::string& str, int i)
{
    std::cout << str << std::endl;
    return 0;
}

int threefunction(const std::string& str, int i, int j)
{
    std::cout << str << std::endl;
    return 0;
}

int fourfunction(const std::string& str, int i, int j, int k)
{
    std::cout << str << std::endl;
    return 0;
}

int main() {
    FunctionSignature<int >::type d = &zerofunction;
    FunctionSignature<int (const std::string& str)>::type f = &onefunction;
    FunctionSignature<int (const std::string& str, int i)>::type a = &twofunction;
    FunctionSignature<int (const std::string& str, int i, int j)>::type b = &threefunction;
    FunctionSignature<int (const std::string& str, int i, int j, int k)>::type c = &fourfunction;
    d();
    f("coucou");
    a("coucou", 1);
    b("coucou", 1, 2);
    c("coucou", 1, 2, 3);
    return 0;
}