//
// Created by consta_n on 9/19/16.
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "ProducterStream.hpp"

ProducterStream::ProducterStream() {
    _ifs = new std::ifstream();
    is_string = false;
    is_end = false;
}

ProducterStream::~ProducterStream() {
    if (_ifs->is_open())
        _ifs->close();
    delete _ifs;
}

std::string ProducterStream::nextString() {

    if (is_end)
        throw std::runtime_error("Fail nextString");
    if (!is_string)
    {
        char _buff[BUFF_SIZE + 1] = {0};
        _stream->read(_buff, BUFF_SIZE);
        std::string res = std::string(_buff);
        if (res.length() == 0)
        {
            if (_ifs->is_open())
                _ifs->close();
            throw std::runtime_error("Fail nextString");
        }
        return res;
    }
    is_end = true;
    return m_str;
}

bool ProducterStream::loadFile(char *path)
{
    if (_ifs->is_open())
        _ifs->close();
    _ifs->open (path);
    //    throw std::runtime_error("Cannot open this file");
    _stream = _ifs;
    return (_ifs->is_open());
}

bool ProducterStream::loadStdin()
{
    if (_ifs->is_open())
        _ifs->close();
    _stream = &std::cin;
    return (_ifs->is_open());
}

bool ProducterStream::loadString(const std::string &str)
{
    is_string = true;
    m_str = str;
    return true;
}


