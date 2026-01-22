#include <iostream>
#include <string>
#include "image_menu.h"

std::string getString( std::istream& is, std::ostream& os, const std::string& prompt ) {
    os << prompt;
    std::string input;
    is >> input;
    return input;
}

int getInteger(std::istream& is, std::ostream& os, const std::string& prompt) {
    os << prompt;
    int value;
    is >> value;
    return value;
}

double getDouble(std::istream& is, std::ostream& os, const std::string& prompt) {
    os << prompt;
    double value;
    is >> value;
    return value;
}

int askQuestions3(std::istream& is, std::ostream& os) {
    std::string color = getString(is, os, "What is your favorite color? ");
    int numLines = getInteger(is, os, "What is your favorite integer? ");
    double favNumber = getDouble(is, os, "What is your favorite number? ");

    for (int i = 1; i <= numLines; ++i) {
        os << i << " " << color << " " << favNumber << "\n";
    }

    return numLines;
}