//
// Created by wery_a on 03/12/16.
//

#include <iostream>
#include "Matcher.hpp"

std::vector<Edge*>  makeEdges(std::string const &str) {
    std::vector<Edge*> str_edges;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        str_edges.push_back(new Edge(*it));
    }
    return str_edges;
}

FSA *mechant() {
    Edge    *le1 = new Edge(-1);
    Edge    *le2 = new Edge(-1);
    Edge    *le3 = new Edge(-1);
    Edge    *le4 = new Edge(-1);

    std::vector<Edge*> mechant = makeEdges("mechant");
    std::vector<Edge*> criminel = makeEdges("criminel");

    std::vector<State*> states;
    for (int i = 0; i < 19; ++i) {
        states.push_back(State::create());
    }

//    Mechant
    states[0]->addLink(le1, states[1]);
    states[1]->addLink(mechant[0], states[2]);
    states[2]->addLink(mechant[1], states[3]);
    states[3]->addLink(mechant[2], states[4]);
    states[4]->addLink(mechant[3], states[5]);
    states[5]->addLink(mechant[4], states[6]);
    states[6]->addLink(mechant[5], states[7]);
    states[7]->addLink(mechant[6], states[8]);
    states[8]->addLink(le3, states[18]);

//    Criminel
    states[0]->addLink(le2, states[9]);
    states[9]->addLink(criminel[0], states[10]);
    states[10]->addLink(criminel[1], states[11]);
    states[11]->addLink(criminel[2], states[12]);
    states[12]->addLink(criminel[3], states[13]);
    states[13]->addLink(criminel[4], states[14]);
    states[14]->addLink(criminel[5], states[15]);
    states[15]->addLink(criminel[6], states[16]);
    states[16]->addLink(criminel[7], states[17]);
    states[17]->addLink(le4, states[18]);

    states[18]->setFinal(true);

    FSA *fsa = new FSA();
    fsa->setInitial(states[0]);
    for (std::vector<State*>::const_iterator it = states.begin(); it != states.end(); ++it) {
        fsa->addState(*it);
    }
    return fsa;
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

int main(int ac, char **av) {
    if (ac < 2) {
        return 1;
    }

//    TODO remove debug and comments
    FSA *fsa1 = mechant();
    FSA *fsa2 = abc();

    int nb_matches;
    bool is;
    FSA *dfa1 = fsa1->subset();
    Matcher *matcherDFA1 = new Matcher(*dfa1);
    for (int i = 1; i < ac; ++i) {
        is = matcherDFA1->find(av[i], nb_matches);
        std::cout << std::boolalpha << is << " " << nb_matches << std::endl;
    }

//    TODO return true mechant on abc

    FSA *dfa2 = fsa2->subset();
    Matcher *matcherDFA2 = new Matcher(*dfa2);
    for (int i = 1; i < ac; ++i) {
        is = matcherDFA2->find(av[i], nb_matches);
        std::cout << std::boolalpha << is << " " << nb_matches << std::endl;
    }
    return 0;
}