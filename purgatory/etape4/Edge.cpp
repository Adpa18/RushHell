//
// Created by wery_a on 03/12/16.
//

#include "Edge.hpp"

Edge::Edge(char c): m_c(c) {

}

Edge::~Edge() {

}

bool Edge::operator()(char c) const {
    return m_c == c;
}

bool Edge::operator==(char c) const {
    return m_c == c;
}

bool Edge::operator==(Edge const &edge) const {
    return m_c == edge.getChar();
}

char Edge::getChar() const {
    return m_c;
}