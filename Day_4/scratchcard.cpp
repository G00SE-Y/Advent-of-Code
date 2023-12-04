#ifndef SCRATCHCARD_H
#define SCRATCHCARD_H

#include "scratchcard.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_set>

typedef struct Card {
    std::vector<int> winners;
    std::unordered_set<int> actual;
    int matches = 0;
    int copies = 1;
}card;

std::regex num_re("[0-9]+");
std::regex pipe_re("[|]+");

std::vector<card> getCards(std::string infile) {

    std::ifstream f (infile);
    std::string ln;

    std::vector<card> cards;

    if(f.is_open()) {
        while(getline(f, ln)) {

            auto rei_begin = std::sregex_iterator(ln.begin(), ln.end(), num_re);
            auto rei_end = std::sregex_iterator();
            rei_begin++; // skip the id number

            card cur_card;
            std::string tmps;
            int tmpn, pos;

            for(auto i = rei_begin; i != rei_end; i++) {

                pos = (*i).position();
                tmps = ln.substr(pos);
                tmpn = std::stoi(tmps);

                if(regex_search(tmps, pipe_re)) {
                    cur_card.winners.push_back(tmpn);
                }
                else {
                    cur_card.actual.insert(tmpn);
                }

            }

            cards.push_back(cur_card);
        }
    }

    f.close();
    return cards;

}

int solution_p1(std::string infile) {

    std::vector<card> cards = getCards(infile);

    int sum = 0;
    
    for(auto c: cards) {

        int i_sum = 0;
        for(auto n: c.winners) {
            if(c.actual.count(n)) {

                i_sum = (i_sum == 0)? 1 : i_sum * 2;
            }
        }
        sum += i_sum;
    }

    return sum;
}

int solution_p2(std::string infile) {

    std::vector<card> cards = getCards(infile);

    int card_count = 0;
    
    for(int i = 0; i < cards.size(); i++) {

        for(auto n: cards[i].winners) {
            if(cards[i].actual.count(n)) {

                cards[i].matches++;
            }
        }

        for(int j = 1; j <= cards[i].matches && i + j < cards.size(); j++) {
            cards[i + j].copies += cards[i].copies;
        }

        card_count += cards[i].copies;
    }

    return card_count;
}

#endif