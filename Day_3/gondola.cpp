#ifndef GONDOLA_H
#define GONDOLA_H

#include "gondola.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

std::regex num_re("[0-9]+"); // matches numerics
std::regex sym_re("[^0-9\\.]+"); // matches anything but numerics or '.'
std::regex star_re("[*]"); // matches '*'

int solution_p1(std::string infile) {

    std::ifstream f (infile);
    std::string ln, tmp, check;
    int sum = 0;

    std::smatch sm;

    std::vector<std::string> box;
    box.reserve(3);

    if(f.is_open()) {
        while(getline(f, ln)) {

            int pos = -1;
            int len = 0;
            box.push_back(ln);
            
            if(box.size() == 2) { // if scanning first line

                while(std::regex_search(box[0], sm, num_re)) { // while a number exists
                    pos = sm.position();
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
                while(std::regex_search(box[1], sm, num_re)) {
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
        while(std::regex_search(box[1], sm, num_re)) {
            
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
    std::string ln, tmp, check;
    int sum = 0;

    std::smatch sm;

    std::vector<std::string> box;
    box.reserve(3);

    if(f.is_open()) {
        while(getline(f, ln)) {

            int pos = -1;
            int len = 0;
            box.push_back(ln);

            for(auto s: box) {
                std::cout << s << std::endl;
            }
            std::cout << std::endl;
            
            if(box.size() == 2) { // if scanning first line

                while(std::regex_search(box[0], sm, star_re)) { // while a gear exists

                    pos = sm.position();
                    len = 2;

                    if(pos > 0 && pos < ln.size()) { pos--; len++; }
                    else if(pos == ln.size() - 1) { pos--; }

                    tmp = box[0].substr(pos, len) + "."
                        + box[1].substr(pos, len);

                    std::cout << "sta  `" << tmp << "`\n" << std::endl;

                    break;
                }
            }
            else if(box.size() == 3) { // scanning any middle line

                while(std::regex_search(box[1], sm, star_re)) { // while a gear exists

                    pos = sm.position();
                    len = 2;

                    if(pos > 0 && pos < ln.size()) { pos--; len++; }
                    else if(pos == ln.size() - 1) { pos--; }

                    tmp = box[0].substr(pos, len) + "."
                        + box[1].substr(pos, len) + "."
                        + box[2].substr(pos, len); 

                    std::cout << "mid  `" << tmp << "`\n" << std::endl;

                    break;
                }

                if(box.size() == 3)
                    box.erase(box.begin());
            }
            
        }

        // scanning last line

    }

    f.close();
    return sum;
}

#endif