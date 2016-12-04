//
// Created by wery_a on 03/12/16.
//

#ifndef RUSHHELL_FSA_HPP
#define RUSHHELL_FSA_HPP

#include <list>
#include "State.hpp"
#include "Closure.h"

//Ensuite, créez une fonction membre statique pour concaténer ou unir deux FSA.
//L’union de deux FSA peut être vue de deux manières différentes. Votre fonction doit pro-
//poser les deux et sera activée via un paramètre optionnel.

class FSA {
public:
    FSA();
    virtual ~FSA();

private:
    std::list<State*>   m_states;
    //std::list<State*>   m_initial_states;
    State*   m_initial_state;

public:
    void    addState(State *state);
    //void    addInitialState(State *state);
    void    setInitial(State * const state);
    //std::list<State*> const &getInitialStates() const;
    State *getInitial() const;
    std::list<State*> const &getStates() const;

public:
    State   *operator[](std::string const &name) const;

public:
    std::list<State*>   closure(std::list<State*> const &states) const;
    std::list<State*>   closure(State *state) const;

public:
    std::list<State*>   move(State *state, Edge *edge) const;
    std::list<State*>   move(LState const &, Edge *edge) const;

public:
    FSA                 *subset() const;

private:
    bool                listNotInList(std::list<State*> const &l1, std::list<State*> const &l2) const;

public:
    static FSA *ConcateFSA(FSA * const f1, FSA * const f2);
    static FSA *MergeFSA(FSA * const f1, FSA * const f2, bool merge_end);
    static FSA *genericFSA(const std::string str);
    static bool exportDOT(FSA *fsa, const std::string &filename);

private:
    static FSA *MergeClose(FSA * const f1, FSA * const f2);
    static FSA *MergeOpen(FSA * const f1, FSA * const f2);
    static bool openFile(const std::string &filename, std::ofstream &fs);
};

void printListState(std::list<State*> list, const std::string &str);

void printListEdge(std::list<Edge*> list, const std::string &str);

std::ostream& operator<<(std::ostream& os, const FSA& fsa);

#endif //RUSHHELL_FSA_HPP

