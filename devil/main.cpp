//
// Created by wery_a on 04/12/16.
//

#include "Inspector.hpp"
//#include "bind/bind.hpp"

struct test{};
struct lol{};

std::ostream& operator<<(std::ostream& out, const lol&)
{
    out << "Lol instance given" ;
    return out;
}

int main() {
    test t;
    lol l;
    std::string str = "salut";
    inspect(t);
    inspect(str);
    inspect(l);
    return 0;
}