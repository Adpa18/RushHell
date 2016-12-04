//
// Created by wery_a on 03/12/16.
//

#ifndef RUSHHELL_FSA_HPP
#define RUSHHELL_FSA_HPP

#include <list>
#include "State.hpp"

//Ensuite, créez une fonction membre statique pour concaténer ou unir deux FSA.
//L’union de deux FSA peut être vue de deux manières différentes. Votre fonction doit pro-
//poser les deux et sera activée via un paramètre optionnel.

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
    static FSA *genericFSA(const std::string str);
    static bool exportDOT(FSA *fsa, const std::string &filename);

private:
    static bool openFile(const std::string &filename, std::ofstream &fs);
};

void printListState(std::list<State*> list, const std::string &str);

void printListEdge(std::list<Edge*> list, const std::string &str);

std::ostream& operator<<(std::ostream& os, const FSA& fsa);

#endif //RUSHHELL_FSA_HPP

