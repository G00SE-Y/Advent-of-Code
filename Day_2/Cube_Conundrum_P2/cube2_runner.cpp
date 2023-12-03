#include <iostream>
#include "Cube2.h"

int main(int argc, char* argv[]) {

    if(argc != 2) {
        std::cout << "Please enter exactly one .txt file name." << std::endl;
        return 0;
    }

    std::cout << "Calculating solution for `" << argv[1] << "` ..." << std::endl;
    int sol = solution(argv[1]);
    std::cout << "Sum of Power of Minimums: " << sol << std::endl;

    return 0;
}