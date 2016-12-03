//
// Created by wery_a on 03/12/16.
//

#include <iostream>
#include "Matcher.hpp"

Matcher::Matcher(FSA const &fsa): m_fsa(fsa) {

}

Matcher::~Matcher() {

}

bool Matcher::find(const std::string &str) const {
    int nb_matches;
    find(str, nb_matches);
}

bool Matcher::find(const std::string &str, int &nb_matches) const {
    std::string build = "";
    nb_matches = 0;

    State *initial = m_fsa.getInitial();
    if (initial == nullptr) {
        return false;
    }
    State *current_state = initial;

    std::vector<Edge*> str_edges = makeEdges(str);

    for (std::vector<Edge*>::const_iterator it = str_edges.begin(); it != str_edges.end(); ++it) {

        std::map<Edge*, State*> const &links = current_state->getLinks();
        for (std::map<Edge*, State*>::const_iterator link = links.begin(); link != links.end(); ++link) {
            if (**it == *(link->first)) {
                build += link->first->getChar();
                current_state = link->second;
                break;
            }
        }
        if (current_state->isFinal()) {
            ++nb_matches;
            current_state = initial;
            build.clear();
        }
    }
    return true;
}

std::vector<Edge*> Matcher::makeEdges(std::string const &str) const {
    std::vector<Edge*> str_edges;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        str_edges.push_back(new Edge(*it));
    }
    return str_edges;
}