#include "camel.h"
#include "Hand.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

struct less_than {
    inline bool operator() (const std::pair<Hand, int> &a, const std::pair<Hand, int> &b) {

        if(a.first.rank < b.first.rank) return true;
        else if(a.first.rank > b.first.rank) return false;

        int i;
        for(i = 0; i < a.first.str.size() && a.first.str[i] == b.first.str[i]; i++);

        return Card_Table.at(a.first.str.substr(i, 1)) > Card_Table.at(b.first.str.substr(i, 1));
    };
};


long long solution_p1(std::string infile) {

    Card_Table.at("J") = 3;

    std::ifstream f (infile);
    std::string ln, hand, bet;
    std::vector<std::pair<Hand, int>> games;

    if(f.is_open()) {
        while(getline(f, ln)) {

            std::istringstream ss(ln);
            ss >> hand;
            ss >> bet;

            Hand cur_hand = Hand(hand);
            games.push_back(std::make_pair(cur_hand, std::stoi(bet)));
        }
    }
    f.close();

    std::sort(games.begin(), games.end(), less_than());

    long long total = 0;
    for(int i = 0; i < games.size(); i++) {
        total += (i + 1) * games[i].second;
    }

    return total;
}

long long solution_p2(std::string infile) {

    Card_Table.at("J") = 13;

    std::ifstream f (infile);
    std::string ln, hand, bet;
    std::vector<std::pair<Hand, int>> games;

    int lns = 0;

    if(f.is_open()) {
        while(getline(f, ln)) {

            std::istringstream ss(ln);
            ss >> hand;
            ss >> bet;
            Hand cur_hand = Hand(hand);
            games.push_back(std::make_pair(cur_hand, std::stoi(bet)));
            
        }
    }
    f.close();

    std::sort(games.begin(), games.end(), less_than());

    long long total = 0;

    for(int i = 0; i < games.size(); i++) {
        total += (i + 1) * games[i].second;
    }

    return total;
}