//
// Created by wery_a on 04/12/16.
//

#include <iostream>
#include "Bind.hpp"

void    test6(std::string i, std::string j, std::string k, std::string l, std::string m, std::string n) {
    std::cout << "cc " << i << j << k << l << m << n << std::endl;
}

void    test5(std::string i, std::string j, std::string k, std::string l, std::string m) {
    std::cout << "cc " << i << j << k << l << m << std::endl;
}

void    test4(std::string i, std::string j, std::string k, std::string l) {
    std::cout << "cc " << i << j << k << l << std::endl;
}

void    test3(std::string i, std::string j, std::string k) {
    std::cout << "cc " << i << j << k << std::endl;
}

void    test2(std::string i, std::string j) {
    std::cout << "cc " << i << j << std::endl;
}

void    test1(std::string i) {
    std::cout << "cc " << i << std::endl;
}

void    testVoid() {
    std::cout << "je suis void" << std::endl;
}

int main() {
    Caller<void, void(*)(void), Traits0::Type> fVoid = bind(&testVoid);
    Caller<void, void(*)(std::string), Traits1<std::string>::Type> f1 = bind(&test1, std::string("aa"));
    Caller<void, void(*)(std::string, std::string), Traits2<std::string, std::string>::Type> f2 = bind(&test2, std::string("aa"), std::string("bb"));
    Caller<void, void(*)(std::string, std::string, std::string), Traits3<std::string, std::string, std::string>::Type> f3 = bind(&test3, std::string("aa"), std::string("bb"), std::string("cc"));
    Caller<void, void(*)(std::string, std::string, std::string, std::string), Traits4<std::string, std::string, std::string, std::string>::Type> f4 = bind(&test4, std::string("aa"), std::string("bb"), std::string("cc"), std::string("dd"));
    Caller<void, void(*)(std::string, std::string, std::string, std::string, std::string), Traits5<std::string, std::string, std::string, std::string, std::string>::Type> f5 = bind(&test5, std::string("aa"), std::string("bb"), std::string("cc"), std::string("dd"), std::string("ee"));
    Caller<void, void(*)(std::string, std::string, std::string, std::string, std::string, std::string), Traits6<std::string, std::string, std::string, std::string, std::string, std::string>::Type> f6 = bind(&test6, std::string("aa"), std::string("bb"), std::string("cc"), std::string("dd"), std::string("ee"), std::string("ff"));
    fVoid();
    f1();
    f2();
    f3();
    f4();
    f5();
    f6();
}