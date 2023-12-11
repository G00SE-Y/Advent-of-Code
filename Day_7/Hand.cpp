#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "Hand.h"

std::map<std::string, int> Card_Table = {
        {"A", 0 },
        {"K", 1 },
        {"Q", 2 },
        {"J", 3 },
        {"T", 4 },
        {"9", 5 },
        {"8", 6 },
        {"7", 7 },
        {"6", 8 },
        {"5", 9 },
        {"4", 10},
        {"3", 11},
        {"2", 12},
};

Hand::Hand(std::string s) {

    str = s;
    Hand::parse_cards();
    Hand::calc_rank();
}

Hand::~Hand() {}

void Hand::calc_rank() {

    std::vector<std::pair<int, int>> values;
    
    for(int i = 0; i < 13; i++) {
        if(counts[i]) {
            values.push_back(std::make_pair(i, counts[i]));
        }
    }

    std::sort(values.begin(), values.end(), [](std::pair<int, int> a, std::pair<int, int> b) { 
            return (a.second == b.second)? a.first < b.first : a.second > b.second; 
    });

    if(Card_Table.at("J") == 13){
        
        if(values.size() == 0) 
            values.push_back(std::make_pair(Card_Table.at("J"), 0));

        values[0].second += jokers;
    }

    if(values.size() == 1) rank = 6;                                // 5 of a kind (5)
    else if(values.size() == 2 && values[0].second == 4) rank = 5;  // 4 of a kind (4, 1)
    else if(values.size() == 2) rank = 4;                           // full house (3, 2)
    else if(values.size() == 3 && values[0].second == 3) rank = 3;  // 3 of a kind (3, 1, 1)
    else if(values.size() == 3) rank = 2;                           // 2 pair (2, 2, 1)
    else if(values.size() == 4) rank = 1;                           // 1 pair (2, 1, 1, 1)
    else rank = 0;                                                  // High card (1, 1, 1, 1, 1)
}

void Hand::parse_cards() {

    std::string tmp = str;
    std::vector<std::string> v;
    
    while(tmp.size() > 0) {
        v.push_back(tmp.substr(0, 1));
        tmp = tmp.substr(1);
        counts[Card_Table.at(v.back())]++;

        if(v.back() == "J") jokers++;
    }
}