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

void unitTestNFAtoDFA()
{

    FSA *m = mechant();
    FSA *c = criminel();
    int nb_matches = 0;

    FSA *merge = FSA::MergeFSA(m, c, true);
    FSA *dfa = merge->subset();
    FSA::exportDOT(merge, "merge");
    Matcher *matcherDFA = new Matcher(*dfa);

    struct test {
        std::string const &text;
        int res;
    };
    const size_t size = 16;
    const test texts[size] = {
            {"mechantmechant", 2},              //1
            {"mechantcriminel", 2},             //2
            {"mechannt", 0},                    //3
            {"crim  inel", 0},                  //4
            {"mechantcriminelmechant", 3},      //5
            {"mechant criminel mechant", 3},    //6
            {"mechmechant", 1},                 //7
            {"mechantmech", 1},                 //8
            {"mechmechantmech", 1},             //9
            {"mecrimihant", 0},                 //10
            {"mechanzdzadtmechant", 1},         //11
            {"me ch ant me ch ant", 0},         //12
            {"mechannnntcriminellmechant", 2},  //13
            {"mechantmecsdDQSqhant", 1},        //14
            {"criminelmechantmechant", 3},      //15
            {"", 0}
    };

    std::cout << "\033[1;33m" << "Start NFA to DFA tests :" << "\033[0m" << std::endl << std::endl;
    for (size_t i = 0; i < size; ++i) {
        matcherDFA->find(texts[i].text, nb_matches);
        assert(nb_matches == texts[i].res);
        std::cout << "\t\033[1;34m" << "test " << i + 1 << "/" << size << " passed" << "\033[0m" << std::endl;
    }
    delete matcherDFA;
    delete dfa;
    delete c;
    delete m;
    delete merge;
    State::freeAll();
    Edge::freeAll();
    std::cout << "\033[1;32mbold" << "Tests NFA to DFA OK" << "\033[0m" << std::endl;
}

int main() {
    unitTestNFAtoDFA();
    return 0;
}