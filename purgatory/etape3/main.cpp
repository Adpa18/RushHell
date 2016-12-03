//
// Created by wery_a on 03/12/16.
//

#include <iostream>
#include "Matcher.hpp"

int main(int ac, char **av) {
    if (ac < 2) {
        return 1;
    }

    Edge    *m = new Edge('m');
    Edge    *e = new Edge('e');
    Edge    *c = new Edge('c');
    Edge    *h = new Edge('h');
    Edge    *a = new Edge('a');
    Edge    *n = new Edge('n');
    Edge    *t = new Edge('t');

    State   *s0 = State::create();
    State   *s1 = State::create();
    State   *s2 = State::create();
    State   *s3 = State::create();
    State   *s4 = State::create();
    State   *s5 = State::create();
    State   *s6 = State::create();
    State   *s7 = State::create();

    s0->addLink(m, s1);
    s1->addLink(e, s2);
    s2->addLink(c, s3);
    s3->addLink(h, s4);
    s4->addLink(a, s5);
    s5->addLink(n, s6);
    s6->addLink(t, s7);
    s7->setFinal(true);

    FSA *fsa = new FSA();
    fsa->setInitial(s0);
    fsa->addState(s0);
    fsa->addState(s1);
    fsa->addState(s2);
    fsa->addState(s3);
    fsa->addState(s4);
    fsa->addState(s5);
    fsa->addState(s6);
    fsa->addState(s7);

    Matcher *matcher = new Matcher(*fsa);
    int nb_matches;
    bool is = matcher->find(av[1], nb_matches);
    std::cout << std::boolalpha << is << " " << nb_matches << std::endl;
    return 0;
}