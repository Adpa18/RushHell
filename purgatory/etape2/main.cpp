#include <iostream>
#include "Machine.hpp"


void    find_string(const std::string &str)
{
    const std::string alphabet = "mechant";
    std::string build = "";
    eState currentState = S0;
    size_t strState = 0;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        strState = alphabet.find(*it);
        if (strState == alphabet.npos) {
            strState = EDGE_MAX;
        }
        switch (gActionTable[currentState][strState]) {
            case MA:
                if (alphabet.find(*it) != alphabet.npos)
                    build += *it;
                currentState = gStateTable[currentState][strState];
                break;
            case HR:
                std::cout << build << std::endl;
                build.clear();
                currentState = S0;
                if (gActionTable[currentState][strState] == MA) {
                    if (alphabet.find(*it) != alphabet.npos)
                        build += *it;
                    currentState = gStateTable[currentState][strState];
                }
                break;
            case ACTION_ERROR:
                build.clear();
                currentState = S0;
                if (gActionTable[currentState][strState] == MA) {
                    if (alphabet.find(*it) != alphabet.npos)
                        build += *it;
                    currentState = gStateTable[currentState][strState];
                }
                break;
        }
    }
    if (currentState == STATE_MAX - 1)
        std::cout << build << std::endl;
}

int main(int ac, char **av)
{
    if (ac < 2) {
        std::cerr << "Usage: ./test_fsa str" << std::endl;
        return 1;
    }
    find_string(av[1]);
    return 0;
}