#ifndef SEEDS_H
#define SEEDS_H

#include "seeds.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>

typedef struct Input {
    std::vector<long long> seeds;
    std::vector<std::map<long long, long long>> maps;
}input;

std::regex num_re = std::regex("[0-9]+");
std::regex alp_re = std::regex("[a-zA-Z]+");

void nstr_into_vec(std::string s, std::vector<long long>& v) {
    
    std::smatch sm;

    auto rei_begin = std::sregex_iterator(s.begin(), s.end(), num_re);
    auto rei_end = std::sregex_iterator();

    for(auto i = rei_begin; i != rei_end; i++) {
        sm = *i;
        v.push_back(std::stoll(sm.str()));
    }
}


input get_input(std::string infile) {

    std::ifstream f(infile);
    std::string ln;
    input in;

    if(f.is_open()) {
        
        getline(f, ln); // get first line
        ln = ln.substr(7); // drop "seeds: "

        nstr_into_vec(ln, in.seeds);

        while(getline(f, ln)) {

            if(std::regex_search(ln, alp_re)) {

                std::map<long long, long long> m;
                long long min = LONG_LONG_MAX;
                
                while(getline(f, ln)) {

                    if(!std::regex_search(ln, num_re)) break;

                    std::vector<long long> v;
                    nstr_into_vec(ln, v);

                    min = (min < v[1])? min : v[1];

                    long long end = v[1] + v[2] - 1; // min + range
                    long long mod = v[0] - v[1]; // diff between mappings

                    m[end] = mod;
                }
                m[min - 1] = 0;
                in.maps.push_back(m);
            }
        }
    }

    f.close();

    return in;
}

long long solution_p1(std::string infile) {

    auto in = get_input(infile);

    for(auto &m: in.maps) {
        for(auto &s: in.seeds) {

            bool found = false;
            for(auto i = m.begin(); i != m.end(); i++) {
                auto cur = *i;
                if( s <= cur.first) {
                    s += cur.second; 
                    found = true;
                    break;
                }
            }
        }
    }

    long long min = LONG_LONG_MAX;
    for(auto l: in.seeds) {
        min = (l < min)? l: min;
    }

    return min;
}

long long solution_p2(std::string infile) {

    auto in = get_input(infile);

    long long t = 0;
    std::vector<long long> new_seeds;
    for(int i = 0; i < in.seeds.size(); i += 2) {
        for(int j = 0; j < in.seeds[i + 1]; j++) {
            // new_seeds.push_back(in.seeds[i] + j);
            t++;
        }
        std::cout << in.seeds[i] << ", ";
    }
    std::cout << std::endl;
    // std::cout << t << std::endl;
    // in.seeds = new_seeds;

    std::vector<std::pair<long long, long long>> input_ranges;
    long long l, r;
    for(auto m: in.maps) {
        l = (*m.begin()).first;
        r = (*m.rbegin()).first;

        l = (l < 0)? 0 : l;
        input_ranges.push_back(std::make_pair(l, r));
    }

    std::vector<std::pair<long long, long long>> output_ranges;
    for(auto m: in.maps) {
        l = LONG_LONG_MAX;
        r = LONG_LONG_MIN;

        for(auto e = m.begin(); e != m.end(); e++) {
            std::cout << (*e).first << " + " << (*e).second << ",  ";

            if((*e).second == 0) {
                l = ((*e).first < l) ? (*e).first : l;
                r = ((*e).first > r) ? (*e).first : r;
            }
            else {
                l = ((*e).first + (*e).second < l) ? (*e).first + (*e).second : l;
                r = ((*e).first + (*e).second > r) ? (*e).first + (*e).second : r;
            }
        }
        std::cout << std::endl;
        l = (l < 0)? 0 : l;
        output_ranges.push_back(std::make_pair(l, r));
    }

    for(int i = 0; i < input_ranges.size(); i++) {
        std::cout << "(" << input_ranges[i].first << "," << input_ranges[i].second << "),  \t" ;
        std::cout << "(" << output_ranges[i].first << "," << output_ranges[i].second << ")" << std::endl;
    }
    std::cout << std::endl;

    for(auto p: output_ranges) {
        
    }
    std::cout << std::endl;

    for(int n = 0; n < in.maps.size(); n++) {

        // for(auto i = in.maps[n].begin(); i != in.maps[n].end(); i++) {
        //     std::cout << (*i).first << " ";
        // }
        // std::cout << std::endl;
        // std::cout << n << std::endl;
        for(auto &s: in.seeds) {

            if(s < input_ranges[n].first || s > input_ranges[n].second) continue;

            bool found = false;
            for(auto i = in.maps[n].begin(); i != in.maps[n].end(); i++) {
                auto cur = *i;
                if( s <= cur.first) {
                    s += cur.second; 
                    found = true;
                    break;
                }
            }
        }
    }

    long long min = LONG_LONG_MAX;
    for(auto l: in.seeds) {
        min = (l < min)? l: min;
    }

    return min;
}

#endif