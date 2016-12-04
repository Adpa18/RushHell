//
// Created by nicolas-constanty on 04/12/16.
//

#include <iostream>
#include "Closure.h"

std::list<Closure*> Closure::_all;

Closure::Closure(const LState &lstate) {

    m_name = "";
    for (LState_it cl = lstate.begin(); cl != lstate.end(); ++cl) {
        m_closure.push_back(*cl);
        m_name += (*cl)->getName();
    }
    _all.push_back(this);
    for (LState_it i = m_closure.begin(); i != m_closure.end() ; ++i) {
        LEdge const &edges = (*i)->getEdges();
        for (LEdge_it j = edges.begin(); j != edges.end(); ++j) {
            m_edges.push_back(*j);
        }
    }
}

Closure::Closure(State *state) {

    m_closure.push_back(state);
}

const LState &Closure::GetClosure() const {
    return m_closure;
}

void Closure::freeAll() {
    std::list<Closure*>::iterator cl = _all.begin();
    while (cl != _all.end()) {
        Closure *tmp = *cl;
        _all.erase(cl++);
        if (tmp != NULL)
            delete tmp;
    }
}

State *Closure::GetState() const {
    State *tmp = new State(m_name);
    return tmp;
}

const std::list<Edge *> &Closure::GetEdges() const
{
    return m_edges;
}

const std::string &Closure::GetName() const
{
    return m_name;
}

//bool State::IsClosure(const std::string &str) const {
//    for (std::list<std::string>::const_iterator i = m_names.begin(); i != m_names.end() ; ++i) {
//        if ((*i) == str)
//            return true;
//    }
//    return false;
//}

std::ostream& operator<<(std::ostream& os, Closure& obj) {

    const LState &lstate = obj.GetClosure();
    os << "Closure -> { ";
    for (LState_it cl = lstate.begin(); cl != lstate.end(); ++cl) {
        os << (*cl)->getName();
        if (cl != --lstate.end())
            os << ", ";
    }
    os << " }";
    return os;
}
