#include "image_menu.h"
#include "PPM.h"
#include <iostream>
#include <string>

void diagonalQuadPattern( ActionData& action_data ) {
    int h = getInteger(action_data, "Image height? ");
    int w = getInteger(action_data, "Image width? ");
    action_data.getInputImage1().setMaxColorValue(255);

    action_data.getInputImage1().setHeight(h);
    action_data.getInputImage1().setWidth(w);

    for (int row = 0; row < h; ++row) {
        for (int column = 0; column < w; ++column) {

            int red;
            int green;
            int blue;

            if (row < h / 2) {
                red = 0;
            } else {
                red = 255;
            }

            if (column < w / 2) {
                blue = 0;
            } else {
                blue = 255;
            }

            green = (2 * row + 2 * column) % 256;

            action_data.getInputImage1().setChannel(row, column, 0, red);    
            action_data.getInputImage1().setChannel(row, column, 1, green);  
            action_data.getInputImage1().setChannel(row, column, 2, blue);  
        }
    }
}


void stripedDiagonalPattern( ActionData& action_data ) {
    int height = getInteger(action_data, "Image height? ");
    int width  = getInteger(action_data, "Image width? ");

    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);

    int max_color = (height + width) / 3;
    if (max_color > 255) max_color = 255;
    action_data.getInputImage1().setMaxColorValue(max_color);

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

            action_data.getInputImage1().setPixel(r, c, red, green, blue);
        }
    }
}


void setSize( ActionData& action_data ) {
    int height = getInteger(action_data, "Height?");
    int width = getInteger(action_data, "Width?");
    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
}

void setMaxColorValue( ActionData& action_data ) {
    int max_color = getInteger(action_data, "Max color value?");
    action_data.getInputImage1().setMaxColorValue(max_color);
}

void setChannel( ActionData& action_data ) {
    int row = getInteger(action_data, "Row?");
    int column = getInteger(action_data, "Column?");
    int channel = getInteger(action_data, "Channel?");
    int value = getInteger(action_data, "Value?");
    action_data.getInputImage1().setChannel(row,column,channel,value);
}

void setPixel( ActionData& action_data ) {
    int row = getInteger(action_data, "Row?");
    int column = getInteger(action_data, "Column?");
    int red = getInteger(action_data, "Red?");
    int green = getInteger(action_data, "Green?");
    int blue = getInteger(action_data, "Blue?");
    action_data.getInputImage1().setPixel(row, column, red, green, blue);
}

void clearAll(ActionData& action_data) {

    for (int row = 0; row < action_data.getInputImage1().getHeight(); ++row) {
        for (int col = 0; col < action_data.getInputImage1().getWidth(); ++col) {
            action_data.getInputImage1().setPixel(row, col, 0, 0,0); 
        }
    }
}
