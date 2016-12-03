//
// Created by wery_a on 03/12/16.
//

#ifndef RUSHHELL_FSA_HPP
#define RUSHHELL_FSA_HPP

#include <list>
#include "State.hpp"

class FSA {
public:
    FSA();
    virtual ~FSA();

private:
    std::list<State*>   m_states;
    State               *m_state_initial;

public:
    void    addState(State *state);
    void    setInitial(State *state);
    State   *getInitial() const;

public:
    State   *operator[](std::string const &name) const;

};

#endif //RUSHHELL_FSA_HPP
