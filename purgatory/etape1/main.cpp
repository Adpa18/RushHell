#include <iostream>
#include "Machine.hpp"

const std::string alphabet = "mechant";

int read_char(char c)
{

}

int peek_char(char c)
{

}

int find_string(const std::string &str)
{
    std::string build = "";
    eState currentState = S0;
    size_t strState = 0;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        strState = alphabet.find(*it);
        if (strState != alphabet.npos) {
            switch (gActionTable[currentState][strState]) {
                case MA:
                    std::cout << "MA" << std::endl;
                    build += *it;
                    currentState = gStateTable[currentState][strState];
                    break;
                case HR:
                    std::cout << "HR" << std::endl;
                    std::cout << build << std::endl;
                    build.clear();
                    --it;
                    currentState = S0;
                    break;
                case ACTION_ERROR:
                    std::cout << "ACTION_ERROR" << std::endl;
                    build.clear();
                    currentState = S0;
                    break;
            }
        }
    }
    std::cout << build << std::endl;
    return 0;
}

int main(int ac, char **av)
{
    if (ac < 2)
        return 1;
    std::cout << find_string(av[1]) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}