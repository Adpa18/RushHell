//
// Created by wery_a on 03/12/16.
//

#include <queue>
#include <algorithm>
#include <iostream>
#include <list>
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
    //df a_states ← 0 {It will hold all DFA states}
    FSA *dfa = new FSA();

    //initial ← closure(S0)
    Closure *initial = new Closure(closure(m_initial_state));
    LState const &cl_states = initial->GetClosure();

    for (LState_it c = cl_states.begin(); c != cl_states.end(); ++c) {
        dfa->addInitialState(*c);
    }
    //processing ← initial {processing is a kind of queue}
    std::queue<Closure *> process;
    process.push(initial);

    //while processing is not empty do
    while (!process.empty()) {
        LState const &lstate = process.front()->GetClosure();
        //current ← pop(processing)
        process.pop();
        for (LState_it cl = lstate.begin(); cl != lstate.end(); ++cl) {
            if (cl == lstate.begin())
                dfa->setInitial(*cl);
            State *current = *cl;
            std::cout << "Current -> "<< *current << std::endl;
            LEdge const &le = current->getEdges();
            //for each edge in alphabet do
            for (LEdge_it e = le.begin(); e != le.end() ; ++e) {
                std::cout << **e << std::endl;
                //states ← move(current, edge)
                LState const &states = move(current, *e);
                for (LState_it t = states.begin(); t != states.end() ; ++t) {
                    std::cout << *(*t) << std::endl;
                }
                //closure ← closure(states)
                Closure *curr_cl = new Closure(closure(states));
                std::cout << "\t" << *curr_cl << std::endl;
                //if closure not in df a_states then
                if (listNotInList(dfa->getStates(), curr_cl->GetClosure()))
                {
                    LState const &cl_states = curr_cl->GetClosure();
                    for (LState_it c = cl_states.begin(); c != cl_states.end(); ++c) {
                        //Add closure to df a_states
                        dfa->addState(*c);
                    }
                    //Push closure to processing
                    if (curr_cl->GetClosure().size())
                        process.push(curr_cl);
                }
                LState const &cl_states = curr_cl->GetClosure();
                for (LState_it c = cl_states.begin(); c != cl_states.end(); ++c) {
                    //Add edge from current to closure
                    current->addLink(*e, (*c));
                }
            }
        }
    }

    return dfa;
//    typedef std::map<State*, std::pair<std::map<Edge*, std::list<State*> >, std::list<State*> > > Coffee;
//
//    Coffee array;
//
//    for (std::list<State*>::const_iterator it = m_states.begin(); it != m_states.end(); ++it) {
//        array[*it].second = closure(*it);
//        std::list<Edge*> edges = (*it)->getEdges();
//        for (std::list<Edge*>::const_iterator edge = edges.begin(); edge != edges.end(); ++edge) {
//            array[*it].first[*edge] = move(*it, *edge);
//        }
//    }
//
//    for (Coffee::const_iterator it = array.begin(); it != array.end(); ++it) {
//        std::cout << (*it).first->getName() << std::endl;
//        for (std::map<Edge*, std::list<State*> >::const_iterator aa = (*it).second.first.begin(); aa != (*it).second.first.end(); ++aa) {
//            std::cout << "Edge " << aa->first->getChar() << std::endl;
//            printListState(aa->second, "move");
//        }
//        printListState((*it).second.second, "closures");
//    }
//
//    std::pair<std::map<Edge *, std::list<State *> >, std::list<State *> > &first = array[*m_initial_states.begin()];
//    std::queue<std::list<State*> > process;
//    process.push(m_initial_states);
//    std::cout << "Process ...\n\n\n" << std::endl;
//    std::list<std::list<State*> > table_verite;
//    table_verite.push_back(m_initial_states);
//    while (!process.empty())
//    {
//        std::list<State*> l = process.front();
//
//        process.pop();
//        for (std::list<State*>::const_iterator it = l.begin(); it != l.end(); ++it) {
//            std::cout << (*it)->getName() << std::endl;
//            for (std::map<Edge*, std::list<State*> >::const_iterator aa = array[*it].first.begin(); aa != array[*it].first.end(); ++aa) {
//                std::list<State*> cl = closure((*aa).second);
//                printListState(cl, "final closure");

//                bool ret = true;
//                for (std::list<std::list<State*> >::const_iterator tab = table_verite.begin(); tab != table_verite.end(); ++tab) {
//                    ret = listNotInList(*tab, cl);
//                    if (!ret) {
//                        break;
//                    }
//                }
//                if (ret) {
//                    process.push(cl);
//                }

//            }
//        }
//    }

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
    //return dfa;
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

State *const &FSA::getInitial() const {
    return m_initial_state;
}

FSA *FSA::ConcateFSA(FSA *const f1, FSA *const f2) {
    FSA *fsa = new FSA();

    LState const &states_f1 = f1->getStates();
    LState const &states_f2 = f2->getStates();
    LState const &initial_states = f1->getInitialStates();
    for (LState_it i = initial_states.begin(); i != initial_states.end() ; ++i) {
        fsa->addInitialState(*i);
    }
    Edge *lambda = new Edge(-1);
    for (LState_it st = states_f1.begin(); st != states_f1.end() ; ++st) {
        fsa->addState(*st);
        if ((*st)->isFinal())
        {
            (*st)->setFinal(false);
            (*st)->addLink(lambda, *f2->getInitialStates().begin());
        }
    }
    for (LState_it st = states_f2.begin(); st != states_f2.end() ; ++st) {
        fsa->addState(*st);
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
    FSA *fsa = new FSA();

    State *start = State::create();
    State *end = State::create();
    end->setFinal(true);

    Edge    *le1 = new Edge(-1);
    Edge    *le2 = new Edge(-1);
    Edge    *le3 = new Edge(-1);
    Edge    *le4 = new Edge(-1);

    start->addLink(le1, *f1->getInitialStates().begin());
    start->addLink(le2, *f2->getInitialStates().begin());

    LState const &states_f1 = f1->getStates();
    LState const &states_f2 = f2->getStates();

    State *final = NULL;
    for (LState_it st = states_f1.begin(); st != states_f1.end() ; ++st) {
        if ((*st)->isFinal())
        {
            final = *st;
            break;
        }
    }
    if (final != NULL)
        final->addLink(le3, end);
    else
        delete le3;
    for (LState_it st = states_f2.begin(); st != states_f2.end() ; ++st) {
        if ((*st)->isFinal())
        {
            final = *st;
            break;
        }
    }
    if (final != NULL)
        final->addLink(le4, end);
    else
        delete le4;
    return fsa;
}

FSA *FSA::MergeOpen(FSA *const f1, FSA *const f2)
{
    FSA *fsa = new FSA();

    State *start = State::create();

    Edge    *le1 = new Edge(-1);
    Edge    *le2 = new Edge(-1);

    start->addLink(le1, *f1->getInitialStates().begin());
    start->addLink(le2, *f2->getInitialStates().begin());

    return fsa;
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