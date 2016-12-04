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
    return find(str, nb_matches);
}

bool Matcher::find(const std::string &str, int &nb_matches) const {
    nb_matches = 0;

    bool ret = false;
    std::vector<Edge*> str_edges = Edge::makeEdges(str);
    State* initial = m_fsa.getInitial();
    if (initial) {
        std::string build = "";
        State *current_state = initial;
        std::vector<Edge*>::const_iterator it = str_edges.begin();
        std::cout << current_state->getName() << std::endl;
        while (it != str_edges.end()) {
            Links const &links = current_state->getLinks();
            for (Links::const_iterator link = links.begin(); link != links.end(); ++link) {
                if (**it == *(link->first)) {
                    std::cout << **it << std::endl;
                    build += link->first->getChar();
                    current_state = link->second;
                    std::cout << current_state->getName() << std::endl;
                }
            }
            if (current_state->isFinal()) {
                ret = true;
                ++nb_matches;
                current_state = initial;
                build.clear();
            }
            ++it;
        }
    }
    return ret;
}