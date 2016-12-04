//
// Created by nicolas-constanty on 04/12/16.
//

#include <fstream>
#include "ExpressionParser.hpp"
#include "Parser.hpp"
#include "FSA.hpp"

ExpressionParser::ExpressionParser(const std::string &alphabet)
{
    ProducterStream ps = ProducterStream();
    Parser parse = Parser(ps);

    std::ofstream	fs;

    ps.loadString(alphabet);
    std::map<std::string, std::string> map;
    FSA *res = NULL;
    if (parse.readExpr(map)) {
        //FSA *last = NULL;
        for (std::map<std::string, std::string>::const_iterator i = map.begin(); i != map.end(); ++i) {
            std::cout << (*i).second << std::endl;
            FSA *tmp = FSA::genericFSA((*i).second);
            if (res != NULL && tmp != NULL)
            {
                res = FSA::MergeFSA(res, tmp, true);
                FSA::exportDOT(res, (*i).second);
                std::cout << "coucou" << std::endl;
            }
            else if (res == NULL)
                res = tmp;
        }
    }

    FSA *dfa = res->subset();
    FSA::exportDOT(dfa, "ameno");
}