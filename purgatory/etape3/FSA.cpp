//
// Created by wery_a on 03/12/16.
//

#include "FSA.hpp"

FSA::FSA(): m_state_initial(nullptr) {

}

FSA::~FSA() {

}

void FSA::addState(State *state) {
    m_states.push_back(state);
}

void FSA::setInitial(State *state) {
    m_state_initial = state;
}

State* FSA::getInitial() const {
    return m_state_initial;
}

State   *FSA::operator[](const std::string &name) const {
    for (std::list<State*>::const_iterator it = m_states.begin(); it != m_states.end(); ++it) {
        if ((*it)->getName() == name) {
            return (*it);
        }
    }
    return nullptr;
}