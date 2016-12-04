//
// Created by wery_a on 03/12/16.
//

#include <queue>
#include <algorithm>
#include <iostream>
#include <list>
#include <fstream>
#include "FSA.hpp"

FSA::FSA() {

}

FSA::~FSA() {
}

void FSA::addState(State *state) {
    if (std::find(m_states.begin(), m_states.end(), state) == m_states.end()) {
        m_states.push_back(state);
    }
}

void FSA::addInitialState(State *state) {
    if (std::find(m_initial_states.begin(), m_initial_states.end(), state) == m_initial_states.end()) {
        m_initial_states.push_back(state);
    }
}

std::list<State*> const& FSA::getInitialStates() const {
    return m_initial_states;
}
std::list<State *> const &FSA::getStates() const {
    return m_states;
}

State   *FSA::operator[](std::string const &name) const {
    for (std::list<State*>::const_iterator it = m_states.begin(); it != m_states.end(); ++it) {
        if ((*it)->getName() == name) {
            return (*it);
        }
    }
    return NULL;
}

void FSA::setInitial(State *const state) {
    m_initial_state = state;
}

State *const &FSA::getInitial() const {
    return m_initial_state;
}

std::ostream& operator<<(std::ostream& os, const FSA& fsa)
{
    LState const &states = fsa.getStates();
    os << "digraph fsa {" << std::endl;
    for (LState_it i = states.begin(); i != states.end(); ++i) {
        os << *(*i);
    }
    os << "}" << std::endl;
    return os;
}

void printListState(std::list<State*> list, const std::string &str) {
    for (std::list<State*>::const_iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << str << " " << (*it)->getName() << std::endl;
    }
}

void printListEdge(std::list<Edge*> list, const std::string &str) {
    for (std::list<Edge*>::const_iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << str << " " << (*it)->getChar() << std::endl;
    }
}

FSA *FSA::genericFSA(const std::string str)
{
    if (str.size())
    {
        FSA *fsa = new FSA();

        std::vector<Edge*> alphabet = Edge::makeEdges(str);
        std::vector<State*> states;
        for (int i = 0; i < alphabet.size() + 1; ++i) {
            states.push_back(State::create());
        }
        fsa->addInitialState(states[0]);
        for (int j = 0; j < states.size(); ++j) {
            if (j + 1 != states.size())
            {
                states[j]->addLink(alphabet[j], states[j + 1]);
            }
            fsa->addState(states[j]);
        }
        states[states.size() -1]->setFinal(true);
        return fsa;
    }
    return NULL;
}

bool FSA::openFile(const std::string &filename, std::ofstream &fs)
{
    fs.open(filename.c_str());
    return fs.is_open();
}

bool FSA::exportDOT(FSA *fsa, const std::string &filename)
{
    std::ofstream	fs;

    if (!openFile("./" + filename + ".dot", fs)) {
        return false;
    }
    fs << (*fsa);
    return true;
}