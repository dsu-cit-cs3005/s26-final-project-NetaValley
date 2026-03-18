#include "image_menu.h"
#include "PPM.h"
#include <iostream>
#include <string>
#include <cmath>

void diagonalQuadPattern(ActionData& action_data) {
    int h = getInteger(action_data, "Image height? ");
    int w = getInteger(action_data, "Image width? ");

    action_data.getInputImage1().setWidth(w);   // width first
    action_data.getInputImage1().setHeight(h);  // then height
    action_data.getInputImage1().setMaxColorValue(255);

    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            int red   = (row < h / 2) ? 0 : 255;
            int blue  = (col < w / 2) ? 0 : 255;
            int green = (2 * row + 2 * col) % 256;

            action_data.getInputImage1().setPixel(row, col, red, green, blue);
        }
    }
}

void stripedDiagonalPattern(ActionData& action_data) {
    int h = getInteger(action_data, "Image height? ");
    int w = getInteger(action_data, "Image width? ");

    action_data.getInputImage1().setWidth(w);   
    action_data.getInputImage1().setHeight(h);

    int max_color = (h + w) / 3;
    if (max_color > 255) max_color = 255;
    action_data.getInputImage1().setMaxColorValue(max_color);

    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            int red = (r < h / 2 || r % 3 == 0) ? 0 : max_color;
            int green = (r + w - c - 1) % (max_color + 1);
            int blue = (c < r) ? 0 : max_color;

            action_data.getInputImage1().setPixel(r, c, red, green, blue);
        }
    }
}

void setSize(ActionData& action_data) {
    int h = getInteger(action_data, "Height? ");
    int w = getInteger(action_data, "Width? ");

    action_data.getInputImage1().heightwidth(h, w);
}

void setMaxColorValue(ActionData& action_data) {
    int max_color = getInteger(action_data, "Max color value? ");
    action_data.getInputImage1().setMaxColorValue(max_color);
}

void setChannel(ActionData& action_data) {
    int row = getInteger(action_data, "Row? ");
    int col = getInteger(action_data, "Column? ");
    int channel = getInteger(action_data, "Channel? ");
    int value = getInteger(action_data, "Value? ");

    action_data.getInputImage1().setChannel(row, col, channel, value);
}

void setPixel(ActionData& action_data) {
    int row = getInteger(action_data, "Row? ");
    int col = getInteger(action_data, "Column? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");

    action_data.getInputImage1().setPixel(row, col, red, green, blue);
}

void clearAll(ActionData& action_data) {
    int h = action_data.getInputImage1().getHeight();
    int w = action_data.getInputImage1().getWidth();

    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            action_data.getInputImage1().setPixel(r, c, 0, 0, 0);
        }
    }
}


void drawCircle(ActionData& action_data){
    int centerrow = getInteger(action_data, "Center Row? ");
    int centercol = getInteger(action_data, "Center Column? ");
    int radius = getInteger(action_data, "Radius? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    for (int row = (centerrow-radius); row <= (centerrow +radius); row++){
        for (int col = (centercol-radius); col <= (centercol+radius); col++){
            double distance = std::sqrt((col-centercol)*(col-centercol) + (row-centerrow)*(row-centerrow));
            if (distance <= radius){
                action_data.getInputImage1().setPixel(row,col,red,green,blue);
            }
        }

    }

}

void drawBox(ActionData& action_data){
    int tRow = getInteger(action_data, "Top Row? ");
    int lCol = getInteger(action_data, "Left Column? ");
    int bRow = getInteger(action_data, "Bottom Row? ");
    int rCol = getInteger(action_data, "Right Column? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");  
    for (int row = tRow; row <= bRow; row ++) {
        for (int col = lCol; col <= rCol; col++){
            action_data.getInputImage1().setPixel(row,col,red,green,blue);
        }
    }
}


void configureGrid(ActionData& action_data){
    int height = getInteger(action_data, "Grid Height? ");
    int width = getInteger(action_data,"Grid Width? ");
    int max = getInteger(action_data,"Grid Max Value? ");
    action_data.getGrid().setGridSize(height, width);
    action_data.getGrid().setMaxNumber(max);
}

void setGrid(ActionData& action_data){
    int row = getInteger(action_data, "Grid Row? ");
    int col = getInteger(action_data,"Grid Column? ");
    int val = getInteger(action_data,"Grid Value? ");
    action_data.getGrid().setNumber(row,col,val);
}

void applyGrid(ActionData& action_data){
    action_data.getGrid().setPPM(action_data.getOutputImage());
}