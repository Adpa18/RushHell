//
// Created by wery_a on 03/12/16.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include "Matcher.hpp"
#include "Parser.hpp"
#include "ExpressionParser.hpp"

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
    for (int i = 0; i < size; ++i) {
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

void unitTestExport()
{
    std::cout << "\033[1;33m" << "Start Export DOT tests :" << "\033[0m" << std::endl << std::endl;

    FSA *m = mechant();
    FSA *c = criminel();

    assert(FSA::exportDOT(m, "mechant"));
    std::cout << "\t\033[1;34m" << "test " << 1 << "/" << 5 << " graph was exported to mechant.dot" << "\033[0m" << std::endl;

    assert(FSA::exportDOT(c, "criminel"));
    std::cout << "\t\033[1;34m" << "test " << 2 << "/" << 5 << " graph was exported to criminel.dot" << "\033[0m" << std::endl;

    FSA *merge1 = FSA::MergeFSA(m, c, false);
    assert(FSA::exportDOT(merge1, "union1"));
    std::cout << "\t\033[1;34m" << "test " << 3 << "/" << 5 << " graph was exported to union1.dot" << "\033[0m" << std::endl;

    delete m;
    delete c;
    delete merge1;
    State::freeAll();
    Edge::freeAll();
    m = mechant();
    c = criminel();

    FSA *merge2 = FSA::MergeFSA(m, c, true);
    assert(FSA::exportDOT(merge2, "union2"));
    std::cout << "\t\033[1;34m" << "test " << 4 << "/" << 5 << " graph was exported to union2.dot" << "\033[0m" << std::endl;

    delete m;
    delete c;
    delete merge2;
    State::freeAll();
    Edge::freeAll();
    m = mechant();
    c = criminel();

    FSA *concat = FSA::ConcateFSA(m, c);
    assert(FSA::exportDOT(concat, "concat"));
    std::cout << "\t\033[1;34m" << "test " << 5 << "/" << 5 << " graph was exported to concat.dot" << "\033[0m" << std::endl;

    delete m;
    delete c;
    delete concat;
    State::freeAll();
    Edge::freeAll();

    std::cout << "\033[1;32mbold" << "Tests Export DOT OK" << "\033[0m" << std::endl;
}

void unitTestExpressionParser()
{
    ExpressionParser exp("(mechant)|(criminel)");
}

void printToken(const std::string &t)
{
    std::cout << t << std::endl;
}

void unitTestStateFunctor()
{
    FSA *m = mechant();
    FSA *c = criminel();

    Function<void(const std::string &)> *f = new Function<void(const std::string &)>(&printToken);
    c->getStates().back()->SetFunction(f);

    FSA *merge = FSA::MergeFSA(m, c, true);

    FSA *dfa = merge->subset();
    Matcher *matcherDFA = new Matcher(*dfa);

    matcherDFA->find("mechant");
}

int main() {
    unitTestNFAtoDFA();
    unitTestExport();
    unitTestExpressionParser();
    unitTestStateFunctor();
    return 0;
}