//
// Created by wery_a on 03/12/16.
//


#include <sstream>
#include <assert.h>
#include "State.hpp"

std::list<State*> State::_all;

size_t State::m_id = 0;

State::State(): m_final(false) {

    std::stringstream ss;
    ss << "S" << m_id;
    m_name = ss.str();
    ++m_id;
    m_func = NULL;
}

State::~State() {

}

bool State::operator==(const std::string &name) const {
    return m_name == name;
}

void State::setName(const std::string &name) {
    m_name = name;
}

const std::string & State::getName() const {
    return m_name;
}

void State::setFinal(bool fin) {
    m_final = fin;
}

bool State::isFinal() const {
    return m_final;
}

State* State::create() {
    State *tmp = new State();
    _all.push_back(tmp);
    return tmp;
}

void State::addLink(Edge *edge, State *state) {
    m_links[edge] = state;
}

Links const& State::getLinks() const {
    return m_links;
}

State *State::operator[](Edge *edge) {
    return m_links[edge];
}

std::list<Edge *> State::getEdges() const {
    std::list<Edge *>   edges;
    for (Links::const_iterator it = m_links.begin(); it != m_links.end(); ++it) {
        edges.push_back(it->first);
    }
    return edges;
}

void State::deleteEdges() {

}

void State::freeAll()
{
    std::list<State*>::iterator states = _all.begin();
    while (states != _all.end()) {
        State *tmp = *states;
        _all.erase(states++);
        if (tmp != NULL)
            delete tmp;
    }
}

void State::SetFunction(Function<void(const std::string &token)> *func) {
    m_func = func;
}

void State::ExecFunc(const std::string &str) const
{
    if (m_func != NULL)
        (*m_func)(str);
}

Function<void(const std::string &token)> *State::GetFunc() const {
    return m_func;
}

void State::DeleteFunc() {
    if (m_func != NULL)
        m_func = NULL;
}

std::ostream& operator<<(std::ostream& os, const State& st)
{
    if (st.isFinal()) {
        os << "  " <<  st.getName() << " [style=\"filled\" color=\"red\"]"<< std::endl;
    }
    Links const &links = st.getLinks();
    for (Links::const_iterator l = links.begin(); l != links.end(); ++l) {
        os << "  " << st.getName() << " -> "
           << (*l).second->getName()
           << " [label=\""
                << (*(*l).first)
           << "\"];" << std::endl;
    }
    return os;
}