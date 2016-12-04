//
// Created by wery_a on 03/12/16.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include "Matcher.hpp"

FSA *criminel() {

    return FSA::genericFSA("criminel");
}

FSA *mechant() {
    return FSA::genericFSA("mechant");
}

FSA *abc() {
    Edge    *le1 = new Edge(-1);
    Edge    *le2 = new Edge(-1);
    Edge    *a1 = new Edge('a');
    Edge    *a2 = new Edge('a');
    Edge    *c1 = new Edge('c');
    Edge    *c2 = new Edge('c');
    Edge    *b1 = new Edge('b');

    State   *s1 = State::create();
    State   *s2 = State::create();
    State   *s3 = State::create();
    State   *s4 = State::create();

    FSA *fsa = new FSA();
    fsa->setInitial(s1);
    s3->setFinal(true);
    s1->addLink(a1, s2);
    s1->addLink(c1, s4);
    s2->addLink(le1, s1);
    s2->addLink(b1, s3);
    s3->addLink(a2, s2);
    s4->addLink(c2, s3);
    s4->addLink(le2, s3);
    fsa->addState(s1);
    fsa->addState(s2);
    fsa->addState(s3);
    fsa->addState(s4);
    return fsa;
}

void unitTestDynamic()
{

    FSA *m = mechant();
    int nb_matches = 0;

    Matcher *matcherDFA = new Matcher(*m);

    struct test {
        std::string const &text;
        int res;
    };
    const size_t size = 3;
    const test texts[size] = {
            {"mechantmechant", 2},              //1
            {"mechannt", 0},                    //2
            {"", 0}                             //3
    };

    std::cout << "\033[1;33m" << "Start Dynamic tests :" << "\033[0m" << std::endl << std::endl;
    for (size_t i = 0; i < size; ++i) {
        matcherDFA->find(texts[i].text, nb_matches);
        assert(nb_matches == texts[i].res);
        std::cout << "\t\033[1;34m" << "test " << i + 1 << "/" << size << " passed" << "\033[0m" << std::endl;
    }
    delete matcherDFA;
    delete m;
    State::freeAll();
    Edge::freeAll();
    std::cout << "\033[1;32mbold" << "Tests Dynamic OK" << "\033[0m" << std::endl;
}

int main() {
    unitTestDynamic();
    return 0;
}