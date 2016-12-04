//
// Created by consta_n on 9/19/16.
//

#ifndef PRODUCTERSTREAM_H
#define PRODUCTERSTREAM_H


#include <string>
#include <istream>

#define BUFF_SIZE 3

class ProducterStream {
private:
    std::ifstream   *_ifs;
    std::istream    *_stream;
    bool is_string;
    bool is_end;
    std::string m_str;
public:
    ProducterStream();
    ~ProducterStream();
    std::string nextString();
    bool loadFile(char *path);
    bool loadStdin();
    bool loadString(const std::string &str);
};


#endif //PYJOUR00_PRODUCTERSTREAM_H
