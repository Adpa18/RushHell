//
// Created by wery_a on 03/12/16.
//

#include <queue>
#include <algorithm>
#include <iostream>
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
    return nullptr;
}

std::list<State*> FSA::closure(std::list<State *> const &states) const {
    std::list<State*>   clinks;
    for (std::list<State*>::const_iterator it = states.begin(); it != states.end(); ++it) {
        clinks.merge(closure(*it));
    }
    return clinks;
}

std::list<State*> FSA::closure(State *state) const {
    std::list<State*>   clinks;

    if (state) {
        clinks.push_back(state);

        Links const &links = state->getLinks();
        for (Links::const_iterator it = links.begin(); it != links.end(); ++it) {
            if (it->first->getChar() == -1) {
                clinks.push_back(it->second);
            }
        }
    }
    return clinks;
}

std::list<State*> FSA::move(State *state, Edge *edge) const {
//    return closure((*state)[edge]);
    State   *current = (*state)[edge];
    std::list<State*>   clinks;

    if (state) {
//        clinks.push_back(current);

        Links const &links = state->getLinks();
        for (Links::const_iterator it = links.begin(); it != links.end(); ++it) {
            if (it->first->getChar() != -1 && it->first == edge) {
                clinks.push_back(it->second);
            }
        }
    }
    return clinks;
}

FSA* FSA::subset() const {
    FSA *dfa = new FSA();

    typedef std::map<State*, std::pair<std::map<Edge*, std::list<State*>>, std::list<State*>>> Coffee;

    Coffee array;

    for (std::list<State*>::const_iterator it = m_states.begin(); it != m_states.end(); ++it) {
        array[*it].second = closure(*it);
        std::list<Edge*> edges = (*it)->getEdges();
        for (std::list<Edge*>::const_iterator edge = edges.begin(); edge != edges.end(); ++edge) {
            array[*it].first[*edge] = move(*it, *edge);
        }
    }

    for (Coffee::const_iterator it = array.begin(); it != array.end(); ++it) {
        std::cout << (*it).first->getName() << std::endl;
        for (std::map<Edge*, std::list<State*>>::const_iterator aa = (*it).second.first.begin(); aa != (*it).second.first.end(); ++aa) {
            std::cout << "Edge " << aa->first->getChar() << std::endl;
            printListState(aa->second, "move");
        }
        printListState((*it).second.second, "closures");
    }

    std::pair<std::map<Edge *, std::list<State *>>, std::list<State *>> &first = array[*m_initial_states.begin()];


//    std::queue<State*> process;
//    std::list<State*>   init_list = closure(m_initial_states);
//    for (std::list<State*>::const_iterator it = init_list.begin(); it != init_list.end(); ++it) {
//        if (it != init_list.begin()) {
//            dfa->addInitialState(*it);
//        }
//        process.push(*it);
//    }
//
//    while (!process.empty()) {
//        State   *current = process.front();
//        process.pop();
//        std::list<Edge*> edges = current->getEdges();
//        std::cout << "Current " << current->getName() << std::endl;
//        printListState(closure(current), "\tClosure");

//        printListEdge(edges, "\tedge");
//        for (std::list<Edge*>::const_iterator edge = edges.begin(); edge != edges.end(); ++edge) {
//            std::list<State*> states = move(current, *edge);
//            std::list<State*> closureStates = closure(states);
//            std::list<State*> dfaStates = dfa->getStates();
//            printListState(states, "\t\tmove");
//            printListState(closureStates, "\t\tclosure ");
//            printListState(dfaStates, "\t\tdfaStates");
//
//            if (listNotInList(closureStates, dfaStates)) {
//                for (std::list<State*>::const_iterator it = closureStates.begin(); it != closureStates.end(); ++it) {
//                    dfa->addState(*it);
//                    process.push(*it);
//                }
//            }
//            for (std::list<State*>::const_iterator it = closureStates.begin(); it != closureStates.end(); ++it) {
//                (*it)->addLink(*edge, current);
//            }
//        }
//    }
    return dfa;
}

bool FSA::listNotInList(std::list<State *> l1, std::list<State *> l2) const {
    for (std::list<State*>::const_iterator it = l1.begin(); it != l1.end(); ++it) {
        if (std::find(l2.begin(), l2.end(), *it) != l2.end()) {
            return false;
        }
    }
    return true;
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