#ifndef TREBUCHET_H
#define TREBUCHET_H

#include "trebuchet.h"

#include <vector>
#include <fstream>
#include <string>
#include <regex>

int solution_p1(std::string infile) {

    std::ifstream f (infile);
    std::string ln;

    std::regex numerics("[^0-9]");
    int sum = 0;
    int num;

    if(f.is_open()) {
        while(getline(f, ln)) {
            ln = std::regex_replace(ln, numerics, "");

            if(ln.size()) {
                num = (ln.front() - 48) * 10 + ln.back() - 48;
            }

            sum += num;
        }
    }

    f.close();
    return sum;
}


std::vector<std::pair<std::regex, std::string>> rs = {
    std::make_pair(std::regex("zero"), "z0o"),
    std::make_pair(std::regex("one"), "o1e"),
    std::make_pair(std::regex("two"), "t2o"),
    std::make_pair(std::regex("three"), "t3e"),
    std::make_pair(std::regex("four"), "f4r"),
    std::make_pair(std::regex("five"), "f5e"),
    std::make_pair(std::regex("six"), "s6x"),
    std::make_pair(std::regex("seven"), "s7n"),
    std::make_pair(std::regex("eight"), "e8t"),
    std::make_pair(std::regex("nine"), "n9e")
};

int solution_p2(std::string infile) {
    
    std::ifstream f (infile);
    std::string ln, ln_old, ln_new;

    std::regex numerics("[^0-9]");
    int sum = 0;
    int num;

    if(f.is_open()) {
        while(getline(f, ln)) {

            for(int i = 0; i < 10; i++) {
                ln = std::regex_replace(ln, rs[i].first, rs[i].second);
            }

            ln = std::regex_replace(ln, numerics, "");

            if(ln.size()) {
                num = (ln.front() - 48) * 10 + ln.back() - 48;
            }

            sum += num;
        }

    }

    f.close();
    return sum;
}

#endif