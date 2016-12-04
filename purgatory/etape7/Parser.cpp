//
// Created by consta_n on 9/19/16.
//


#include <iostream>
#include <sstream>
#include "Parser.hpp"

Parser::Parser(ProducterStream &ps) : ConsumerParser(ps)
{}

bool Parser::repeater(Function<bool(void)> func, char c)
{
    if (c == '?')
    {
        func();
        return (true);
    }
    else if (c == '*')
    {
        while (!readEOF() && func());
        return (true);
    }
    else if (c == '+' && func())
    {
        while (!readEOF() && func());
        return (true);
    }
    return (false);
}

//Expr ::= [ InterExpr ]* ;
//InterExpr ::= SubExpr '|'
//SubExpr ::= '(' [ Str ]* ')';
//Str ::= a-z | A-Z
bool Parser::interStr(std::map<std::string,std::string>& content)
{
    return (
            readSubExpr(content)
            || readChar('|')
    );
}

size_t Parser::m_id = 0;
bool Parser::readExpr(std::map<std::string,std::string>& content)
{

    while (!readEOF() && interStr(content));
    return (true);
}

bool Parser::readStr(std::map<std::string, std::string> &content) {
    std::stringstream ss;
    ss << "S" << m_id;
    ++m_id;
    beginCapture(ss.str());
    bool ret = readIdentifier();
    if (ret)
        endCapture(ss.str(), content[ss.str()]);
    return (ret);
}

bool Parser::readSubExpr(std::map<std::string,std::string>& content)
{
    return (
            readChar('(')
            || readStr(content)
            || readChar(')')
    );
}

////Header ::=  CMD ' ' URI ' ' VERSION '\n' [HeaderList #flush ]*;
//bool Parser::readHeader(std::map<std::string,std::string>& content)
//{
//    //bool ret = readCMD();
//    //std::cout << std::boolalpha << ret << std::endl;
//    return (readCMD() && readChar(' ') && readURI() && readChar(' ') && readVersion() && readChar('\n') && repeater([&content, this] () { return (readHeaderList(content));}, '*'));
//}
//
////CMD ::= «GET» | «POST» ;
//bool Parser::readCMD()
//{
//    return (true);
//}

////URI ::= ['/'|'.'|'?'|'%'|'&'|'='|'+'|':'|'-'|'a'..'z'|'A'..'Z'|'0'..'9']+;
//bool Parser::readURI()
//{
//    return (repeater([this] () { return (
//            readChar('/')
//            || readChar('.')
//            || readChar('?')
//            || readChar('%')
//            || readChar('&')
//            || readChar('=')
//            || readChar('+')
//            || readChar(':')
//            || readChar('-')
//            || readRange('a', 'z')
//            || readRange('A', 'Z')
//            || readRange('0', '9'));}, '+'));
//}
//
////VERSION ::= «http/1.0»;
//bool Parser::readVersion()
//{
//    return (readText((char *) "http/1.0"));
//}
//
////HeaderList ::= HeaderName ':' data;
//bool Parser::readHeaderList(std::map<std::string,std::string>& content)
//{
//    return (repeater([this, &content] () {
//        bool ret = readHeaderName() && readChar(':');
//        if (ret && !_tmp_data.empty())
//            beginCapture(_tmp_data);
//        ret = (ret && readData());
//        if (!_tmp_data.empty())
//            endCapture(_tmp_data, content[_tmp_data]);
//        _tmp_data.clear();
//        return ret;
//    }, '+'));
//}
//
////HeaderName ::= ['-'|'a'..'z'|'A'..'Z']+;
//bool Parser::readHeaderName()
//{
//    bool ret;
//    beginCapture("Name");
//    ret = repeater([this] () { return (readChar('-') || readRange('a', 'z') || readRange('A', 'Z')); }, '+');
//    endCapture("Name", _tmp_data);
//    return (ret);
//}
//
////data ::= → '\n';
//bool  Parser::readData()
//{
//    return (readUntil('\n'));
//}
//
////Body ::= → EOF //tout jusqu'à EOF;
//bool Parser::readBody()
//{
//    return (readUntilEOF());
//}
