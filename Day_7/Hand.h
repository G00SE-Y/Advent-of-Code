#ifndef HAND_H
#define HAND_H

#include <string>
#include <map>
#include <vector>

class Hand {

    public:

    std::string str = "";
    int rank = 0;

    Hand(std::string s);
    ~Hand();

    private:

    int counts[14] = {0};
    int jokers = 0;

    void calc_rank();
    void parse_cards();
};

extern std::map<std::string, int> Card_Table;

#endif