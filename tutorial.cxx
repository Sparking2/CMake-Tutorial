// A simple program that computes the square root of a number
#include <cmath>
#include <iostream>
#include <string>

// TODO 5:  Include MathFunctions.h
#include "TutorialConfig.h"

int main(int argc, char *argv[])
{
    // report version
    std::cout << "Version: " << Tutorial_VERSION_MAJOR << "." << Tutorial_VERSION_MINOR << std::endl;

    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    // convert input to double
    const double inputValue = std::stod(argv[1]);

    // TODO 6: Replace sqrt with mathfunctions::sqrt

    // calculate square root
    const double outputValue = sqrt(inputValue);
    std::cout << "The square root of " << inputValue << " is " << outputValue << std::endl;
    return 0;
}