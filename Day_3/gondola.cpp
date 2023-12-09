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
    long long sum = 0;

    std::smatch sm;

    std::vector<std::string> box;
    box.reserve(3);

    if(f.is_open()) {
        while(getline(f, ln)) {
            std::cout << "current sum: " << sum << std::endl;

            int pos = -1;
            int len = 0;
            box.push_back(ln);

            // for(auto s: box) {
            //     std::cout << s << std::endl;
            // }
            // std::cout << std::endl;
            
            if(box.size() == 2) { // if scanning first line

                while(std::regex_search(box[0], sm, star_re)) { // while a gear exists

                    pos = sm.position();
                    len = 2;

                    if(pos > 0 && pos < ln.size()) { pos--; len++; }
                    else if(pos == ln.size() - 1) { pos--; }

                    tmp = box[0].substr(pos, len) + "."
                        + box[1].substr(pos, len);

                    std::cout << "sta  `" << tmp << "`\n" << std::endl;

                    int count = std::distance(std::sregex_iterator(tmp.begin(), tmp.end(), num_re), std::sregex_iterator());

                    if(count == 2) {

                        int prod = 1;
                        std::vector<std::vector<bool>> marks = {
                            {false, true , false},
                            {false, false, false}
                        };

                        for(int i = 0; i < 2; i++) {
                            for(int j = pos + len - 1; j >= 0 && j >= pos; j--) {

                                if(marks[i][j - pos] == true) continue;
                                marks[i][j - pos] = true;

                                if(std::regex_search(box[i].substr(j, 1), num_re)) {
                                    
                                    int start = j;
                                    while(start - 1 >= 0 && std::regex_search(box[i].substr(start - 1, 1), num_re)) {
                                        
                                        if(j >= pos) marks[i][j - pos] = true;
                                        start--;
                                    }

                                    if(start >= pos) marks[i][start - pos] = true;
                                    std::cout << "Found: " << std::stoi(box[i].substr(start)) << std::endl;
                                    prod = prod * std::stoi(box[i].substr(start));
                                }
                            }
                        }
                        sum += prod;
                    }
                    box[0][pos + 1] = '.';
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

                    int count = std::distance(std::sregex_iterator(tmp.begin(), tmp.end(), num_re), std::sregex_iterator());

                    if(count == 2) {

                        int prod = 1;
                        std::vector<std::vector<bool>> marks = {
                            {false, false, false},
                            {false, true , false},
                            {false, false, false}
                        };

                        for(int i = 0; i < 3; i++) {
                            for(int j = pos + len - 1; j >= 0 && j >= pos; j--) {

                                if(marks[i][j - pos] == true) continue;
                                marks[i][j - pos] = true;

                                if(std::regex_search(box[i].substr(j, 1), num_re)) {
                                    
                                    int start = j;
                                    while(start - 1 >= 0 && std::regex_search(box[i].substr(start - 1, 1), num_re)) {
                                        
                                        if(j >= pos) marks[i][j - pos] = true;
                                        start--;
                                    }

                                    if(start >= pos) marks[i][start - pos] = true;

                                    std::cout << "Found: " << std::stoi(box[i].substr(start)) << std::endl;

                                    prod = prod * std::stoi(box[i].substr(start));
                                }
                            }
                        }
                        sum += prod;
                    }
                    box[1][pos + 1] = '.';
                }

                if(box.size() == 3)
                    box.erase(box.begin());
            }
            
        }

        // scanning last line
        // for(auto s: box) {
        //     std::cout << s << std::endl;
        // }
        // std::cout << std::endl;

        int pos, len;
        while(std::regex_search(box[0], sm, star_re)) { // while a gear exists

            pos = sm.position();
            len = 2;

            if(pos > 0 && pos < ln.size()) { pos--; len++; }
            else if(pos == ln.size() - 1) { pos--; }

            tmp = box[0].substr(pos, len) + "."
                + box[1].substr(pos, len);

            std::cout << "end  `" << tmp << "`\n" << std::endl;

            int count = std::distance(std::sregex_iterator(tmp.begin(), tmp.end(), num_re), std::sregex_iterator());

            if(count == 2) {

                int prod = 1;
                std::vector<std::vector<bool>> marks = {
                    {false, false, false},
                    {false, true , false}
                };

                for(int i = 0; i < 2; i++) {
                    for(int j = pos + len - 1; j >= 0 && j >= pos; j--) {

                        if(marks[i][j - pos] == true) continue;
                        marks[i][j - pos] = true;

                        if(std::regex_search(box[i].substr(j, 1), num_re)) {
                            
                            int start = j;
                            while(start - 1 >= 0 && std::regex_search(box[i].substr(start - 1, 1), num_re)) {
                                
                                if(j >= pos) marks[i][j - pos] = true;
                                start--;
                            }

                            if(start >= pos) marks[i][start - pos] = true;

                            std::cout << "Found: " << std::stoi(box[i].substr(start)) << std::endl;
                            prod = prod * std::stoi(box[i].substr(start));
                        }
                    }
                }
                sum += prod;
            }
            box[1][pos + 1] = '.';
        }

    }

    f.close();
    return sum;
}

#endif