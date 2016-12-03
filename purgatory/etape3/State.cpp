//
// Created by wery_a on 03/12/16.
//

#include "State.hpp"

size_t State::m_id = 0;

State::State() {
    m_name = "S" + m_id;
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

std::map<Edge*, State*> const& State::getLinks() const {
    return m_links;
}