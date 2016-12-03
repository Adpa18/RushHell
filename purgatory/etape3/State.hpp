//
// Created by wery_a on 03/12/16.
//

#ifndef RUSHHELL_STATE_HPP
#define RUSHHELL_STATE_HPP

#include <cstring>
#include <map>
#include "Edge.hpp"

class State {
private:
    State();
    virtual ~State();

private:
    static size_t           m_id;
    std::string             m_name;
    bool                    m_final;
    std::map<Edge*, State*> m_links;

public:
    bool    operator==(std::string const &name) const;

public:
    void                setName(std::string const &name);
    std::string const   &getName() const;

public:
    void                setFinal(bool fin);
    bool                isFinal() const;

public:
    static State        *create();

public:
    void    addLink(Edge *edge, State *state);
    std::map<Edge*, State*> const   &getLinks() const;
};

#endif //RUSHHELL_STATE_HPP
