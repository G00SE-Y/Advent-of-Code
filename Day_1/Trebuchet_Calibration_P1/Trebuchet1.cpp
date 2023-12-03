#include <vector>
#include <fstream>
#include <string>
#include <regex>

#ifndef TREBUCHET_1_H
#define TREBUCHET_1_H

#include "Trebuchet1.h"

int solution(std::string infile) {

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

#endif