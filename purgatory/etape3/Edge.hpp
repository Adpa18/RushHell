//
// Created by wery_a on 03/12/16.
//

#ifndef RUSHHELL_EDGE_HPP
#define RUSHHELL_EDGE_HPP

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

#endif //RUSHHELL_EDGE_HPP
