#include <iostream>
#include <string>
#include "image_menu.h"

std::string getString( ActionData& action_data, const std::string& prompt ) {
    std::string value;
    action_data.getOS() << prompt;
    action_data.getIS() >> value;
    return value;
}

int getInteger(ActionData& action_data, const std::string& prompt) {
    int value;
    action_data.getOS() << prompt;
    action_data.getIS() >> value;
    return value;
}

double getDouble(ActionData& action_data, const std::string& prompt) {
    double value;
    action_data.getOS() << prompt;
    action_data.getIS() >> value;
    return value;
}

int askQuestions3(ActionData& action_data) {
    std::string color = getString(action_data, "What is your favorite color? ");
    int numLines = getInteger(action_data, "What is your favorite integer? ");
    double favNumber = getDouble(action_data, "What is your favorite number? ");

    for (int i = 1; i <= numLines; ++i) {
        action_data.getOS() << i << " " << color << " " << favNumber << "\n";
    }

    return numLines;
}

std::string getChoice( ActionData& action_data ) {
    std::string value = getString(action_data, "Choice? ");
    return value;
}


void commentLine(ActionData& action_data) {
    char c;

    while (true) {
        action_data.getIS().read(&c, 1);

        if (!action_data.getIS().good()) {
            return;
        }

        if (c == '\n') {
            return;
        }
    }
}

void quit(ActionData& action_data) {
    action_data.setDone();
}