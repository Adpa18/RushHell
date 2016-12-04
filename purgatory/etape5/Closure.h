//
// Created by nicolas-constanty on 04/12/16.
//

#ifndef TEST_NSA_TO_DFA_CLOSURE_H
#define TEST_NSA_TO_DFA_CLOSURE_H

#include "State.hpp"

class Closure {
public:
    Closure(const LState &lstate);

private:
    Closure(State *state);

    LState m_closure;

public:
    const LState &GetClosure() const;
};

std::ostream& operator<<(std::ostream& os, Closure& obj);

#endif //TEST_NSA_TO_DFA_CLOSURE_H
