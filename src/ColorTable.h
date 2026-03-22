#pragma once 
#include <iostream>
#include <vector>



class Color {
private:
    int red;
    int green;
    int blue;
public:
    Color( ); //Sets all color channels to value 0.
    Color( const int& red, const int& green, const int& blue ); //Sets the color channels to the values provided here. No range checking is applied.
    int getRed( ) const; //Returns the value of the red channel.
    int getGreen( ) const; //Returns the value of the green channel.
    int getBlue( ) const; //Returns the value of the blue channel.
    int getChannel( const int& channel ) const; //Returns the value of the channelth channel. 0 == red, 1 == green, 2 == blue. Returns -1 if the channel is out of range.
    void setRed( const int& value ); //Changes the red channel to value. If value is less than 0, do not make any changes.
    void setGreen( const int& value ); //Changes the green channel to value. If value is less than 0, do not make any changes.
    void setBlue( const int& value ); //Changes the blue channel to value. If value is less than 0, do not make any changes.
    void setChannel( const int& channel, const int& value ); //Changes the channelth channel to value. If value is less than 0, do not make any changes. 0 == red, 1 == green, 2 == blue. Does not make changes if channel is out of range.
    void invert( const int& max_color_value ); //Inverts the red, green and blue channels, using max_color_value. If max_color_value is less than any of the current color channels (red, green or blue), then make no changes. The inversion is completed by subtracting the current value from max_color_value. For example: red = max_color_value - red. This only makes sense if red is <= max_color_value. That’s why we make no changes if any channel (red, green or blue) is larger than max_color_value.
    bool operator==( const Color& rhs ) const; //Returns true if *this and rhs have the same color values. Otherwise, returns false.

};

class ColorTable {
private:
    std::vector<Color> Colors;
public: 
    ColorTable( const int& num_color ); //Sizes the Color collection to num_color items.
    int getNumberOfColors( ) const; //Returns the number of Colors stored.
    void setNumberOfColors( const int& num_color ); //Resizes the collection to hold num_color items. Previous Color contents may or may not be preserved.
    const Color& operator[]( const int& i ) const; //Returns the ith Color in the collection. If i is out of range, returns a static memory Color object with all three channels set to -1. See an example below.
    Color& operator[]( const int& i ); //Returns the ith Color in the collection. If i is out of range, returns a static memory Color object with all three channels set to -1.
    void setRandomColor( const int& max_color_value, const int& position ); //Assigns the positionth color random values for all three channels. The random values are between 0 and max_color_value, inclusive. If position is out of range, no change is made. If max_color_value is less than 0, no change is made. This method should NOT use std::srand() Add std::srand(std::time(0)); to main() of ppm_menu.cpp.
    double gradientSlope(const double y1, const double y2, const double x1, const double x2) const; //Calculates a slope from point 1 to point 2, using “rise-over-run” calculation. Be sure to use floating point division operation.
    double gradientValue(const double y1, const double x1, const double slope, const double x) const; //Calculate the y-value along the gradient from point (x1,y1) to the point at position x.
    void insertGradient( const Color& color1, const Color& color2, const int& position1, const int& position2 ); //Change the colors from position1 to position2, inclusive, to be gradients from color1 to color2. If position1 is not less than position2, no change is made. If either position is out of range, no change is made. Should use the gradientSlope() and gradientValue() methods.
    int getMaxChannelValue( ) const; //Finds the largest value of any red, greeen, or blue value in any color in the table.
};

std::ostream& operator<<( std::ostream& os, const Color& color );