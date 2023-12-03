#include <iostream>
#include <string.h>
#include "cube.h"

int main(int argc, char* argv[]) {

    if(argc != 3) {
        std::cout << "Please enter input in the form `./cube.exe [ \"p1\" | \"p2\" ] <*.txt>`" << std::endl;
        return 0;
    }

    if(strcmp(argv[1], "p1") == 0) {

        std::cout << "Calculating solution for Part 1 using `" << argv[2] << "` ..." << std::endl;
        int sol = solution_p1(argv[2]);
        std::cout << "Sum of Possible Game IDs: " << sol << std::endl;
    }
    else if(strcmp(argv[1], "p2") == 0) {

        std::cout << "Calculating solution for Part 2 using `" << argv[2] << "` ..." << std::endl;
        int sol = solution_p2(argv[2]);
        std::cout << "Sum of Minimum Powers: " << sol << std::endl;
    }
    else {
        std::cout << "Can't you follow instructions?!" << std::endl; 
    }

    std::cout << std::endl;

    return 0;
}