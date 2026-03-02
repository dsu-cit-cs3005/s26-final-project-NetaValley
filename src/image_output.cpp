#include "ActionData.h"
#include "image_menu.h"
#include <iostream>
#include <fstream>
#include <string>

void drawAsciiImage(ActionData& action_data)
{
    const int height = action_data.getOutputImage().getHeight();
    const int width  = action_data.getOutputImage().getWidth();

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            int red   = action_data.getOutputImage().getChannel(row, col, 0);
            int green = action_data.getOutputImage().getChannel(row, col, 1);
            int blue  = action_data.getOutputImage().getChannel(row, col, 2);

 
            double strength = (red + green + blue) / 765.0;

            char outputChar;

            if      (strength >= 1.0) outputChar = '@';
            else if (strength >= 0.9) outputChar = '#';
            else if (strength >= 0.8) outputChar = '%';
            else if (strength >= 0.7) outputChar = '*';
            else if (strength >= 0.6) outputChar = '|';
            else if (strength >= 0.5) outputChar = '+';
            else if (strength >= 0.4) outputChar = ';';
            else if (strength >= 0.3) outputChar = '~';
            else if (strength >= 0.2) outputChar = '-';
            else if (strength >= 0.1) outputChar = '.';
            else outputChar = ' ';  

            action_data.getOS() << outputChar;
        }
        action_data.getOS() << '\n';
    }
}


void writeUserImage(ActionData& action_data) {
    std::string filename = getString(action_data, "Output filename? ");
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile)
    {
        action_data.getOS() << "Error: could not open output file.\n";
        return;
    }
    action_data.getOutputImage().writeStream(outFile);
    outFile.close();
}

void copyImage(ActionData& action_data){
    action_data.getOutputImage() = action_data.getInputImage1();
}

void readUserImage1( ActionData& action_data ) {
    std::string filename = getString(action_data, "Input filename? ");
    std::ifstream fin(filename);

    if (!fin.is_open()) {
        action_data.getOS() << "'" << filename << "' could not be opened.\n";
        return;
    }

    action_data.getInputImage1().readStream(fin);
}


void readUserImage2( ActionData& action_data ) {
    std::string filename = getString(action_data, "Input filename? ");
    std::ifstream fin(filename);

    if (!fin.is_open()) {
        action_data.getOS() << "'" << filename << "' could not be opened.\n";
        return;
    }

    action_data.getInputImage2().setHeight(0);
     action_data.getInputImage2().setWidth(0);
    action_data.getInputImage2().setMaxColorValue(255);

    action_data.getInputImage2().readStream(fin);
}