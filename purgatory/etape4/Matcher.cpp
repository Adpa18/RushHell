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

    std::vector<Edge*> str_edges = makeEdges(str);
    std::list<State*> inits = m_fsa.getInitialStates();
    for (std::list<State*>::const_iterator initial = inits.begin(); initial != inits.end(); ++initial) {
        if (*initial) {
            std::string build = "";
            State *current_state = *initial;

//            std::cout << *current_state << std::endl;
            std::vector<Edge*>::const_iterator it = str_edges.begin();
            while (it != str_edges.end()) {
                Links const &links = current_state->getLinks();
                for (Links::const_iterator link = links.begin(); link != links.end(); ++link) {
                    //std::cout << **it << "---" << *(link->first) << std::endl;
                    if (**it == *(link->first)) {
                        build += link->first->getChar();
                        current_state = link->second;
                        break;
                    }
                }
                if (current_state->isFinal()) {
//                    std::cout << build << std::endl;
                    ++nb_matches;
                    current_state = *initial;
                    build.clear();
                }
                ++it;
                //if (it == str_edges.end())
                //    return true;
            }

        }
    }
//    std::cout << std::endl;
    return true;
}

std::vector<Edge*> Matcher::makeEdges(std::string const &str) const {
    std::vector<Edge*> str_edges;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        str_edges.push_back(new Edge(*it));
    }
    return str_edges;
}