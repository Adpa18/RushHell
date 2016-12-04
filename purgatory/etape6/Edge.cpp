//
// Created by wery_a on 03/12/16.
//

#include "Edge.hpp"

Edge::Edge(char c): m_c(c) {
    all.push_back(this);
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

std::list<Edge*> Edge::all;

std::vector<Edge*>  Edge::makeEdges(std::string const &str) {
    std::vector<Edge*> str_edges;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        str_edges.push_back(new Edge(*it));
    }
    return str_edges;
}

void Edge::freeAll()
{
    std::list<Edge*>::iterator edges = all.begin();
    while (edges != all.end()) {
        Edge *tmp = *edges;
        all.erase(edges++);
        if (tmp != NULL)
            delete tmp;
    }
}

std::ostream& operator<<(std::ostream& os, const Edge& obj)
{
    os << "Edge -> " << obj.getChar();
    return os;
}