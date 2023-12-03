#ifndef GONDOLA_H
#define GONDOLA_H

#include "gondola.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

int solution_p1(std::string infile) {

    std::ifstream f (infile);
    std::string ln, tmp, check;
    int sum = 0;

    std::regex num_re("[0-9]+");
    std::regex sym_re("[^0-9\\.]+");
    std::smatch sm;

    std::vector<std::string> box;
    box.reserve(3);

    if(f.is_open()) {
        while(getline(f, ln)) {

            int pos = -1;
            int len = 0;
            box.push_back(ln);
            
            if(box.size() == 2) { // if scanning first line

                while(std::regex_search(box[0], sm, num_re, std::regex_constants::format_first_only)) {
                    pos = sm.position(0);
                    len = sm.length();

                    tmp = box[0].substr(pos, len); // copy
                    box[0].replace(pos, len, len, '.'); // replace

                    if(pos > 0) {pos--; len++; }
                    if(pos + len < ln.size()) len++;

                    check = box[0].substr(pos, len) +
                            box[1].substr(pos, len);

                    if(std::regex_search(check, sym_re)) {
                        sum += std::stoi(tmp);
                    }
                }
            }
            else if(box.size() == 3) { // scanning any middle line
                while(std::regex_search(box[1], sm, num_re, std::regex_constants::format_first_only)) {
                    pos = sm.position();
                    len = sm.length();

                    tmp = box[1].substr(pos, len); // copy
                    box[1].replace(pos, len, len, '.'); // replace

                    if(pos > 0) {pos--; len++; }
                    if(pos + len < ln.size()) len++;

                    check = box[0].substr(pos, len) +
                            box[1].substr(pos, len) +
                            box[2].substr(pos, len);


                    if(std::regex_search(check, sym_re)) {
                        sum += std::stoi(tmp);
                    } 
                }
            }

            if(box.size() == 3)
                box.erase(box.begin());
            
        }

        // scanning last line
        int pos = -1;
        int len = 0;
        while(std::regex_search(box[1], sm, num_re, std::regex_constants::format_first_only)) {
            
            pos = sm.position();
            len = sm.length();

            tmp = box[1].substr(pos, len); // copy
            box[1].replace(pos, len, len, '.'); // replace

            if(pos > 0) {pos--; len++; }
            if(pos + len < ln.size()) len++;

            check = box[0].substr(pos, len) +
                    box[1].substr(pos, len);


            if(std::regex_search(check, sym_re)) {
                sum += std::stoi(tmp);
            }
        }
    }

    f.close();
    return sum;
}

int solution_p2(std::string infile) {

    std::ifstream f (infile);
    std::string ln;

    if(f.is_open()) {
        while(getline(f, ln)) {
            std::cout << ln << std::endl;
        }
    }

    f.close();
    return 0;
}

#endif