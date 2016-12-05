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
    m_initial_state = NULL;
}

FSA::~FSA() {
}

void FSA::addState(State *state) {
    if (std::find(m_states.begin(), m_states.end(), state) == m_states.end()) {
        m_states.push_back(state);
    }
}

//void FSA::addInitialState(State *state) {
//    if (std::find(m_initial_states.begin(), m_initial_states.end(), state) == m_initial_states.end()) {
//        m_initial_states.push_back(state);
//    }
//}

//std::list<State*> const& FSA::getInitialStates() const {
//    return m_initial_states;
//}
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

std::list<State*> FSA::closure(std::list<State *> const &states) const {
    std::list<State*>   clinks;
    for (std::list<State*>::const_iterator it = states.begin(); it != states.end(); ++it) {
        LState  l = closure(*it);
        for (LState_it i = l.begin(); i != l.end() ; ++i) {
            clinks.push_back(*i);
        }
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
                LState const &c = closure((*it).second);
                for (LState_it i = c.begin(); i != c.end() ; ++i) {
                    clinks.push_back(*i);
                }
            }
        }
    }
    return clinks;
}

std::list<State*> FSA::move(State *state, Edge *edge) const {
    std::list<State*>   clinks;

    if (state) {
        Links const &links = state->getLinks();
        for (Links::const_iterator it = links.begin(); it != links.end(); ++it) {
            if (it->first->getChar() != -1 && it->first == edge) {
                clinks.push_back(it->second);
            }
        }
    }
    return clinks;
}

std::list<State*> FSA::move(LState const &st, Edge *edge) const {
    std::list<State*>   clinks;
    for (LState_it i = st.begin(); i != st.end(); ++i) {
        LState const &tmp = move(*i, edge);
        for (LState_it j = tmp.begin(); j != tmp.end() ; ++j) {
            clinks.push_back(*j);
        }
    }
    return clinks;
}

FSA* FSA::subset() const {
    FSA *dfa = new FSA();

    Closure *initial = new Closure(closure(m_initial_state));
    std::queue<Closure *> processing;
    processing.push(initial);
    State *start = initial->GetState();
    dfa->setInitial(start);
    dfa->addState(start);
    std::cout << "Current : " << initial->GetName() << std::endl;
    while (!processing.empty())
    {
        Closure *current = processing.front();
        std::cout << "Current : " << current->GetName() << std::endl;
        processing.pop();
        LState const &cl_states = current->GetClosure();
        std::list<Edge *> alpha;
        for (LState_it state_closure = cl_states.begin(); state_closure != cl_states.end(); ++state_closure) {
            LEdge const &e = (*state_closure)->getEdges();
            for (LEdge_it i = e.begin(); i != e.end(); ++i) {
                if ((*i)->getChar() != -1)
                    alpha.push_back(*i);
            }
        }
        LEdge const &edges = alpha;
        if (alpha.size() == 0)
            (*dfa)[current->GetName()]->setFinal(true);
        for (LEdge_it i = edges.begin(); i != edges.end(); ++i) {
            std::cout << "edge : " << **i << std::endl;
            LState const &states = move(current->GetClosure(), *i);
            bool find = false;
            LState const &dfa_state = dfa->getStates();
            Closure *cl = new Closure(closure(states));
            State *closure = cl->GetState();
            for (LState_it df = dfa_state.begin(); df != dfa_state.end() ; ++df) {
                if ((*df)->getName() == cl->GetName())
                {
                    find = true;
                    break;
                }
            }
            if (!find)
            {
                dfa->addState(closure);
                processing.push(cl);
            }
            (*dfa)[current->GetName()]->addLink(*i, closure);
        }
    }
    std::cout << *dfa << dfa->getStates().size() << std::endl;
    return dfa;
}

bool FSA::listNotInList(std::list<State *> const &l1, std::list<State *> const &l2) const {
    for (std::list<State*>::const_iterator it = l1.begin(); it != l1.end(); ++it) {
        if (std::find(l2.begin(), l2.end(), *it) != l2.end()) {
            return false;
        }
    }
    return true;
}

void FSA::setInitial(State *const state) {
    m_initial_state = state;
}

State  *FSA::getInitial() const {
    return m_initial_state;
}

FSA *FSA::ConcateFSA(FSA *const f1, FSA *const f2) {
    FSA *fsa = new FSA();

    LState const &states_f1 = f1->getStates();
    LState const &states_f2 = f2->getStates();
    State *start = f1->getInitial();

    fsa->setInitial(start);

    Edge *lambda = new Edge(-1);
    for (LState_it st = states_f1.begin(); st != states_f1.end() ; ++st) {
        fsa->setInitial(*st);
        if ((*st)->isFinal())
        {
            (*st)->setFinal(false);
            (*st)->addLink(lambda, f2->getInitial());
        }
    }
    for (LState_it st = states_f2.begin(); st != states_f2.end() ; ++st) {
        fsa->setInitial(*st);
    }
    return fsa;
}

FSA *FSA::MergeFSA(FSA *const f1, FSA *const f2, bool merge_end) {

    if (merge_end)
        return MergeClose(f1, f2);
    else
        return MergeOpen(f1, f2);
}

FSA *FSA::MergeClose(FSA *const f1, FSA *const f2)
{
//    FSA *fsa = new FSA();
//
//    State *start = State::create();
//    State *end = State::create();
//
//
//    Edge    *le1 = new Edge(-1);
//    Edge    *le2 = new Edge(-1);
//    Edge    *le3 = new Edge(-1);
//    Edge    *le4 = new Edge(-1);
//
//    std::cout << f2->getInitial()->getName() << std::endl;
//    std::cout << f1 << std::endl;
//    start->addLink(le1, f1->getInitial());
//    start->addLink(le2, f2->getInitial());
//
//    fsa->addInitialState(start);
//    fsa->setInitial(start);
//    fsa->addState(start);
//
//    fsa->addState(end);
//
//    LState const &states_f1 = f1->getStates();
//    LState const &states_f2 = f2->getStates();
//
//    end->setFinal(true);
//    State *final = NULL;
//    for (LState_it st = states_f1.begin(); st != states_f1.end() ; ++st) {
//        fsa->addState(*st);
//        LEdge const &edge = (*st)->getEdges();
//        for (LEdge_it i = edge.begin(); i != edge.end(); ++i) {
//            std::cout << (*i)->getChar() << std::endl;
//        }
//        if ((*st)->isFinal())
//        {
//            (*st)->setFinal(false);
//            final = *st;
//            break;
//        }
//    }
//    if (final != NULL)
//        final->addLink(le3, end);
//    else
//        delete le3;
//    for (LState_it st = states_f2.begin(); st != states_f2.end() ; ++st) {
//        fsa->addState(*st);
//        if ((*st)->isFinal())
//        {
//            (*st)->setFinal(false);
//            final = *st;
//            break;
//        }
//    }
//    if (final != NULL)
//        final->addLink(le4, end);
//    else
//        delete le4;
    FSA *fsa = new FSA();

    State *start = State::create();
    State *end = State::create();

    Edge    *le1 = new Edge(-1);
    Edge    *le2 = new Edge(-1);
    Edge    *le3 = new Edge(-1);
    Edge    *le4 = new Edge(-1);

    start->addLink(le1, f1->getInitial());
    start->addLink(le2, f2->getInitial());

    LState const &states_f1 = f1->getStates();
    LState const &states_f2 = f2->getStates();

    fsa->setInitial(start);
    fsa->addState(start);
    for (LState_it st = states_f1.begin(); st != states_f1.end() ; ++st) {
        fsa->addState(*st);
        if ((*st)->isFinal())
        {
            (*st)->setFinal(false);
            end->setFinal(true);
            (*st)->addLink(le3, end);
        }
    }
    for (LState_it st = states_f2.begin(); st != states_f2.end() ; ++st) {
        fsa->addState(*st);
        if ((*st)->isFinal())
        {
            (*st)->setFinal(false);
            end->setFinal(true);
            (*st)->addLink(le4, end);
        }
    }
    fsa->addState(end);
    return fsa;
}

FSA *FSA::MergeOpen(FSA *const f1, FSA *const f2)
{
    FSA *fsa = new FSA();

    State *start = State::create();

    Edge    *le1 = new Edge(-1);
    Edge    *le2 = new Edge(-1);

    start->addLink(le1, f1->getInitial());
    start->addLink(le2, f2->getInitial());

    LState const &states_f1 = f1->getStates();
    LState const &states_f2 = f2->getStates();

    fsa->setInitial(start);
    fsa->addState(start);
    for (LState_it st = states_f1.begin(); st != states_f1.end() ; ++st) {
        fsa->addState(*st);
    }
    for (LState_it st = states_f2.begin(); st != states_f2.end() ; ++st) {
        fsa->addState(*st);
    }
    return fsa;
}

std::ostream& operator<<(std::ostream& os, const FSA& fsa)
{
    LState const &states = fsa.getStates();
    os << "digraph fsa {" << std::endl;
    for (LState_it i = states.begin(); i != states.end(); ++i) {
        os << **i;
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
        for (size_t i = 0; i < alphabet.size() + 1; ++i) {
            states.push_back(State::create());
        }
        fsa->setInitial(states[0]);
        for (size_t j = 0; j < states.size(); ++j) {
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