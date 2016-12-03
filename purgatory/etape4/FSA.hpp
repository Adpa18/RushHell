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
    std::list<State*>   m_initial_states;

public:
    void    addState(State *state);
    void    addInitialState(State *state);
    std::list<State*> const &getInitialStates() const;
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
    bool                listNotInList(std::list<State*> l1, std::list<State*> l2) const;
};

void printListState(std::list<State*> list, const std::string &str);

void printListEdge(std::list<Edge*> list, const std::string &str);

#endif //RUSHHELL_FSA_HPP

