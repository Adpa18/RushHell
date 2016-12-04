//
// Created by nicolas-constanty on 04/12/16.
//

#include <iostream>
#include "Closure.hpp"

std::list<Closure*> Closure::_all;

Closure::Closure(const LState &lstate) {

    for (LState_it cl = lstate.begin(); cl != lstate.end(); ++cl) {
        m_closure.push_back(*cl);
    }
    _all.push_back(this);
}

Closure::Closure(State *state) {

    m_closure.push_back(state);
}

const LState &Closure::GetClosure() const {
    return m_closure;
}

void Closure::freeAll() {
    std::list<Closure*>::iterator cl = _all.begin();
    while (cl != _all.end()) {
        Closure *tmp = *cl;
        _all.erase(cl++);
        if (tmp != NULL)
            delete tmp;
    }
}

std::ostream& operator<<(std::ostream& os, Closure& obj) {

    const LState &lstate = obj.GetClosure();
    os << "Closure -> { ";
    for (LState_it cl = lstate.begin(); cl != lstate.end(); ++cl) {
        os << (*cl)->getName();
        if (cl != --lstate.end())
            os << ", ";
    }
    os << " }";
    return os;
}
