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
        FSA *last = NULL;

        for (std::map<std::string, std::string>::const_iterator i = map.begin(); i != map.end(); ++i) {
            FSA *tmp = FSA::genericFSA((*i).second);
            if (last != NULL)
                res = FSA::MergeFSA(last, tmp, true);
            last = tmp;
        }
    }
    FSA::exportDOT(res, "ameno");
}