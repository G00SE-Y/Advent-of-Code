#include <iostream>
#include "Trebuchet2.h"

int main(int argc, char* argv[]) {

    if(argc != 2) {
        std::cout << "Please enter exactly one .txt file name." << std::endl;
        return 0;
    }

    std::cout << "Calculating solution for `" << argv[1] << "` ..." << std::endl;
    int sol = solution(argv[1]);
    std::cout << "Final Calibration: " << sol << std::endl;

    return 0;
}