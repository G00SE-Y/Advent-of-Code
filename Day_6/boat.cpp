#ifndef BOAT_H
#define BOAT_H

#include "boat.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

std::vector<std::vector<int>> parse_input_p1(std::string infile) {
    std::ifstream f (infile);
    std::string ln;

    std::regex num_re("[0-9]+");

    std::vector<std::vector<int>> v = {{}, {}};

    if(f.is_open()) {

        for(int i: {0, 1}) {
            getline(f, ln);

            auto rei_begin = std::sregex_iterator(ln.begin(), ln.end(), num_re);
            auto rei_end = std::sregex_iterator();

            for(auto it = rei_begin; it != rei_end; it++) {
                
                v[i].push_back(std::stoi((*it).str()));
            }
        }
    }

    f.close();
    return v;
}

std::vector<long long> parse_input_p2(std::string infile) {
    std::ifstream f (infile);
    std::string ln;

    std::regex num_re("[0-9]+");
    std::regex space_re("\\s");

    std::vector<long long> v;

    if(f.is_open()) {

        std::smatch sm;
        std::string s;

        getline(f, ln);

        std::regex_search(ln, sm, num_re);
        s = ln.substr(sm.position());
        s = std::regex_replace(s, space_re, "");
        v.push_back(std::stoll(s));

        getline(f, ln);

        std::regex_search(ln, sm, num_re);
        s = ln.substr(sm.position());
        s = std::regex_replace(s, space_re, "");
        v.push_back(std::stoll(s));

    }

    f.close();
    return v;
}

int solution_p1(std::string infile) {

    auto in = parse_input_p1(infile);

    std::vector<int> counts(in[0].size(), 0);

    for(int i = 0; i < in[0].size(); i++) {

        for(int n = 0; n <= in[0][i]; n++) {
            if((in[0][i] - n) * n > in[1][i]) counts[i]++;
        }
    }

    int product = 1;
    for(auto i: counts) {
        product *= i;
    }

    return product;
}

int solution_p2(std::string infile) {

    auto in = parse_input_p2(infile);

    int count = 0;

    for(int n = 0; n <= in[0]; n++) {

        if((in[0] - n) * n > in[1]) count++;
    }
    
    return count;
}

#endif