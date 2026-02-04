#include "image_menu.h"
#include <iostream>
#include <fstream>
#include <string>

void drawAsciiImage( std::istream&, std::ostream& os, const Image& image )
{
    for (int row = 0; row < image.getHeight(); row++)
    {
        for (int column = 0; column < image.getWidth(); column++)
        {
            int red   = image.getChannel(row, column, 0);
            int green = image.getChannel(row, column, 1);
            int blue  = image.getChannel(row, column, 2);

            double strength = (red + green + blue) / 765.0;

            char outputChar = ' ';

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

            os << outputChar;
        }
        os << '\n';
    }
}


void writeUserImage( std::istream& is, std::ostream& os, const PPM& p ) {
        // Ask user for filename
    std::string filename = getString(is, os, "Output filename? ");

    // Open file in binary mode
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile)
    {
        os << "Error: could not open output file.\n";
        return;
    }

    // Write PPM data to file
    p.writeStream(outFile);

    // Close the file
    outFile.close();
}