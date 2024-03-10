//
// Created by adrozdov on 18/02/24.
//

#include "engine.h"
#include <sstream>
#include <fstream>

Line::Line(std::string& s, char sep) {
    // Init container and split input string
    this->elems = std::vector<std::string>();
    this->separator = sep;

    std::stringstream ss(s);
    std::string token;
    while(std::getline(ss, token, sep)){
        this->elems.push_back(token);
    }
}

std::string Line::operator[](int i) {
    // Wrapper to ignore out of bounds error
    if(i >= this->elems.size()){
        return "";
    }
    return this->elems[i];
}

std::string Line::all() {
    std::string res;
    for(int i=0;i<this->length();i++){
        res += this->elems[i];
        if(i < this->length() - 1){
            res += this->separator;
        }
    }
    return res;
}

Engine::Engine(char sep, std::ifstream *input) {
    this->input = input;
    this->separator = sep;
    this->current_line = nullptr;
}

void Engine::print_elems(std::vector<int> &pos) {
    if(this->current_line == nullptr){
        return;
    }

    for(int i=0;i<pos.size();i++){
        std::cout << this->current_line->operator[](pos[i]);
        if(i < pos.size() - 1)
            std::cout << this->separator;
    }

    std::cout << std::endl;
}

std::string Engine::get_str(int pos) {
    if(this->current_line == nullptr){
        return "";
    }
    return this->current_line->operator[](pos);
}

std::string Engine::full_str() {
    if(this->current_line == nullptr){
        return "";
    }
    return this->current_line->all();
}

void Engine::reset_stream() {
    this->input->clear();
    this->input->seekg(0);
}

bool Engine::parse_line() {
    std::string s;
    bool l = bool(std::getline(*(this->input), s));
    delete this->current_line;
    this->current_line = new Line(s, this->separator);
    //printf("CURRENT LINE: %s\n", s.c_str());
    return l;
}
