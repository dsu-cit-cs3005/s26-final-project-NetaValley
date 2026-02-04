#include "image_menu.h"
#include "PPM.h"
#include <iostream>

void diagonalQuadPattern(std::istream& is, std::ostream& os, Image& image) {
    // Declare height and width
    int h = getInteger(is, os, "Image height? ");
    int w = getInteger(is, os, "Image width? ");

    // Set the image size
    image.setHeight(h);
    image.setWidth(w);

    // Loop through every pixel
    for (int row = 0; row < h; ++row) {
        for (int column = 0; column < w; ++column) {

            int red;
            int green;
            int blue;

            // Red channel: top half vs bottom half
            if (row < h / 2) {
                red = 0;
            } else {
                red = 255;
            }

            // Blue channel: left half vs right half
            if (column < w / 2) {
                blue = 0;
            } else {
                blue = 255;
            }

            // Green channel: formula
            green = (2 * row + 2 * column) % 256;

            // Set the channels in the Image object
            image.setChannel(row, column, 0, red);    // Red
            image.setChannel(row, column, 1, green);  // Green
            image.setChannel(row, column, 2, blue);   // Blue
        }
    }
}


void stripedDiagonalPattern(std::istream& is, std::ostream& os, PPM& p) {
    int height = getInteger(is, os, "Image height? ");
    int width  = getInteger(is, os, "Image width? ");

    p = PPM(height, width);

    int max_color = (height + width) / 3;
    if (max_color > 255) max_color = 255;
    p.setMaxColorValue(max_color);

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {

            int red;
            if (r < height / 2) {
                red = 0;
            } else if (r % 3 == 0) {
                red = 0;
            } else {
                red = max_color;
            }

            int green = (r + width - c - 1) % (max_color + 1);

            int blue = (c < r) ? 0 : max_color;

            p.setPixel(r, c, red, green, blue);
        }
    }
}