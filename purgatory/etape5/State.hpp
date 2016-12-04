//
// Created by wery_a on 03/12/16.
//

#ifndef RUSHHELL_STATE_HPP
#define RUSHHELL_STATE_HPP

#include <string>
#include <cstring>
#include <map>
#include <list>
#include "Edge.hpp"

class State;
typedef std::map<Edge*, State*> Links;

class State {
private:
    State();
    static std::list<State*> _all;


public:
    static void freeAll();
    virtual ~State();

private:
    static size_t           m_id;
    std::string             m_name;
    bool                    m_final;
    Links                   m_links;

public:
    bool    operator==(std::string const &name) const;

public:
    void                setName(std::string const &name);
    std::string const   &getName() const;

public:
    void                setFinal(bool fin);
    bool                isFinal() const;
    void                deleteEdges();

public:
    static State        *create();

public:
    void    addLink(Edge *edge, State *state);
    Links const     &getLinks() const;
    State           *operator[](Edge *edge);
    std::list<Edge*>    getEdges() const;
};

std::ostream& operator<<(std::ostream& os, const State& obj);

typedef std::list<State*> LState;
typedef std::list<State*>::const_iterator LState_it;

#endif //RUSHHELL_STATE_HPP
