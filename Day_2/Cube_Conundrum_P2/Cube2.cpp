#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <regex>

#ifndef CUBE_2_H
#define CUBE_2_H

#include "Cube2.h"

std::map<std::string, int> counts = {
    {"red", 12},
    {"green", 13},
    {"blue", 14}
};

std::map<std::string, int> colors = {
    {"red", 0},
    {"green", 1},
    {"blue", 2}
};

std::vector<std::string> split(std::string str, std::regex re) {
    std::vector<std::string> splits;
    std::smatch sm;

    while (std::regex_search(str, sm, re)){

        int pos = sm.position();
        
        if(!str.substr(0, pos).empty())
            splits.push_back(str.substr(0, pos));

        str = str.substr(pos + sm.length());
    }

    if(!str.empty()) {
        splits.push_back(str);
    }

    return splits;
}

std::pair<int, std::vector<std::vector<int>>> parseLine(std::string ln) {

    std::string tmp;

    std::vector<std::vector<int>> games;
    int id = 0;

    int pos1, pos2;

    // Get ID
    pos1 = ln.find("Game ") + 5;
    pos2 = ln.find(": ");
    tmp = ln.substr(pos1, pos2 - pos1);
    id = std::stoi(tmp);

    // std::cout << "ID: " << id << std::endl;

    ln.erase(0, pos2 + 2);

    auto hands = split(ln, std::regex("[;]"));
    for(auto hand: hands) {

        std::vector<int> game_hand(3, 0);
        
        auto hand_colors = split(hand, std::regex("[ |,]"));

        for(int i = 0; i < hand_colors.size(); i += 2) {

            game_hand[colors[hand_colors[i + 1]]] = std::stoi(hand_colors[i]);
        }

        games.push_back(game_hand);
    }

    return std::make_pair(id, games);
}

std::vector<int> minPossible(std::vector<std::vector<int>> game) {

    std::vector<int> min(3, 0);

    for(auto v: game) {
        
        if(v[0] > min[0])
            min[0] = v[0];

        if(v[1] > min[1])
            min[1] = v[1];
        
        if(v[2] > min[2])
            min[2] = v[2];
            
    }

    return min;
}

int solution(std::string infile) {

    std::ifstream f (infile);
    std::string ln;

    int sum = 0;

    while(std::getline(f, ln)) {
        // std::cout << ln << std::endl;

        auto game = parseLine(ln);

        std::vector<int> min = minPossible(game.second);
        sum += min[0] * min[1] * min[2];
    }

    f.close();

    return sum;
}

#endif