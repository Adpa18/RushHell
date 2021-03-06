//
// Created by consta_n on 9/19/16.
//

#include <stdexcept>
#include <iostream>
#include "ConsumerParser.hpp"

ConsumerParser::ConsumerParser(ProducterStream &ps) : _ps(ps)
{
    _tag = "";
    _ignore = "";
    _comment = -1;
}

bool ConsumerParser::readText(char *text)
{
    std::string save;

    save = _buffer;
    while (text[0] != 0)
    {

        if (!readChar(*text))
        {
            _buffer = save;
            return (false);
        }
        ++text;
    }
    return (true);
}

bool ConsumerParser::readEOF()
{
    try {
        if (_buffer.empty())
            _buffer += _ps.nextString();
    }
    catch (std::runtime_error e)
    {
        return (true);
    }
    return (false);
}

bool ConsumerParser::readUntil(char c)
{
    std::string save;

    save = _buffer;
    while (!readEOF())
    {
        if (readChar(c))
            return (true);
        else
        {
            if (!_tag.empty())
                _capture[_tag] += _buffer[0];
            _buffer = _buffer.substr(1);
        }
    }
    _buffer = save;
    return (false);
}

bool ConsumerParser::readUntilEOF()
{
    while (!readEOF())
    {
        if (!_tag.empty())
            _capture[_tag] += _buffer[0];
        _buffer = _buffer.substr(1);
    }
    return (true);
}

bool ConsumerParser::readInteger()
{
    bool ret = false;
    while (!readEOF())
    {
        if (!readRange('0', '9'))
            return (ret);
        else
            ret = true;
    }
    return (ret);
}

 bool ConsumerParser::readIdentifier()
{
    bool ret = false;
    if (readRange('a', 'z') || readRange('A', 'Z') || readChar('_'))
    {
        ret = true;
        while (!readEOF())
        {
            if (!readRange('0', '9') && !readRange('a', 'z') && !readRange('A', 'Z') && !readChar('_'))
                return (ret);
        }
    }
    return (ret);
}

bool ConsumerParser::readValue()
{
   bool ret = false;
   if (readRange('0', '9') || readRange('a', 'z') || readRange('A', 'Z') || readChar('_')  || readChar('/'))
   {
       ret = true;
       while (!readEOF())
       {
           if (!readRange('0', '9') && !readRange('a', 'z') && !readRange('A', 'Z') && !readChar('_') && !readChar('/'))
               return (ret);
       }
   }
   return (ret);
}
