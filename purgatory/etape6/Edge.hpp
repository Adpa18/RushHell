//
// Created by wery_a on 03/12/16.
//

#ifndef RUSHHELL_EDGE_HPP
#define RUSHHELL_EDGE_HPP

#include <list>
#include <iostream>

class Edge {
public:
    Edge(char c);
    virtual ~Edge();

    bool    operator()(char c) const;
    bool    operator==(char c) const;
    bool    operator==(Edge const &edge) const;

public:
    char    getChar() const;

private:
    char    m_c;
};

typedef std::list<Edge*> LEdge;
typedef std::list<Edge*>::const_iterator LEdge_it;

std::ostream& operator<<(std::ostream& os, const Edge& obj);

#endif //RUSHHELL_EDGE_HPP
