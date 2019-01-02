//
// Created by kyle on 1/1/19.
//

#include <iostream>
#include <sstream>
#include "args.h"

std::pair<int, int> getDimsFromString(const std::string& str) {

    static std::string errorString = "Error: Bad dimensions argument given. Example: 100x100";

    auto xPos = str.find('x');
    if (xPos != std::string::npos) {

        std::string widthString(str.substr(0, xPos));
        std::string heightString(str.substr(xPos + 1));

        if (widthString.empty() ||
            heightString.empty()) {

            std::cout << errorString << "\n";
            return {-1, -1};
        }

        return {getNumFromString(widthString),
               getNumFromString(heightString)};
    }
    else {
        std::cout << errorString << "\n";
        return {-1, -1};
    }

}

int getNumFromString(const std::string& str) {

    int ret;

    if (!(std::stringstream(str) >> ret)) {
        std::cout << "Error: bad dimension given. Please enter an integer\n";
        return -1;
    }

    return ret;
}