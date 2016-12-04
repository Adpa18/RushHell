//
// Created by wery_a on 03/12/16.
//

#ifndef RUSHHELL_MATCHER_HPP
#define RUSHHELL_MATCHER_HPP

#include <vector>
#include "FSA.hpp"

class Matcher {
public:
    Matcher(FSA const &fsa);
    virtual ~Matcher();

private:
    FSA const   &m_fsa;

public:
    bool    find(std::string const &str) const;
    bool    find(std::string const &str, int &nb_matches) const;
};

#endif //RUSHHELL_MATCHER_HPP
