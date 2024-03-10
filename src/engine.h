//
// Created by adrozdov on 18/02/24.
//

#ifndef HAWK_ENGINE_H
#define HAWK_ENGINE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Line {
private:
    char separator;
    std::vector<std::string> elems;
public:
    inline int length() { return this->elems.size(); }
    std::string all();
    std::string operator[](int i);
    Line(std::string& s, char sep);
};

class Engine
{
private:
    char separator;
    Line *current_line;
    std::ifstream *input;

public:
    bool parse_line();
    void reset_stream();
    void print_elems(std::vector<int> &pos);
    std::string get_str(int pos);
    std::string full_str();
    Engine(char sep, std::ifstream *input);
    // FIXME: destructor!
};

#endif //HAWK_ENGINE_H
