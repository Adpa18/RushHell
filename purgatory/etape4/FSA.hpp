//
// Created by wery_a on 03/12/16.
//

#ifndef RUSHHELL_FSA_HPP
#define RUSHHELL_FSA_HPP

#include <list>
#include "State.hpp"
#include "Closure.h"

class FSA {
public:
    FSA();
    virtual ~FSA();

private:
    std::list<State*>   m_states;
    std::list<State*>   m_initial_states;
    State*   m_initial_state;

public:
    void    addState(State *state);
    void    addInitialState(State *state);
    void    setInitial(State * const state);
    std::list<State*> const &getInitialStates() const;
    State* const &getInitial() const;
    std::list<State*> const &getStates() const;

public:
    State   *operator[](std::string const &name) const;

public:
    std::list<State*>   closure(std::list<State*> const &states) const;
    std::list<State*>   closure(State *state) const;

public:
    std::list<State*>   move(State *state, Edge *edge) const;

public:
    FSA                 *subset() const;

private:
    bool                listNotInList(std::list<State*> const &l1, std::list<State*> const &l2) const;
};

void printListState(std::list<State*> list, const std::string &str);

void printListEdge(std::list<Edge*> list, const std::string &str);

#endif //RUSHHELL_FSA_HPP

