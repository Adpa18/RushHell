//
// Created by consta_n on 9/19/16.
//

#ifndef PYJOUR00_PARSERHTTP_H
#define PYJOUR00_PARSERHTTP_H

#include "ConsumerParser.hpp"
#include "Function.hpp"

class Parser : public ConsumerParser
{
public:
    Parser(ProducterStream &);
    bool readExpr(std::map<std::string, std::string> &);
    std::string     _tmp_data;

private:
    bool readSubExpr(std::map<std::string,std::string>& content);
    bool readStr(std::map<std::string,std::string>& content);
    bool interStr(std::map<std::string,std::string>& content);
    static size_t   m_id;
//    bool readVersion();
//
//    bool readCMD();
//
//    bool readHeaderName();
//
//    bool readURI();
//
//    bool readData();
//
//    bool readBody();
//
//    bool readHeader(std::map<std::string,std::string>& content);
//
//    bool readHeaderList(std::map<std::string,std::string>& content);

    bool repeater(Function<bool()> func, char c);
};


#endif //PYJOUR00_PARSERHTTP_H
