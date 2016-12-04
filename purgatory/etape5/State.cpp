//
// Created by wery_a on 03/12/16.
//


#include <sstream>
#include "State.hpp"

size_t State::m_id = 0;

State::State(): m_final(false) {

    std::stringstream ss;
    ss << "S" << m_id;
    m_name = ss.str();
    ++m_id;
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
    return new State();
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

std::ostream& operator<<(std::ostream& os, const State& obj)
{
    os << "State -> " << obj.getName();
    return os;
}