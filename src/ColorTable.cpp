#include "ColorTable.h"



Color::Color( ) :
    red(0), green(0),blue(0){}//Sets all color channels to value 0.
Color::Color( const int& red, const int& green, const int& blue ){
   this->red = red;
   this-> green = green;
   this-> blue = blue;
} //Sets the color channels to the values provided here. No range checking is applied.

int Color::getRed( ) const{
    return red;
} //Returns the value of the red channel.

int Color::getGreen( ) const{
    return green;
} //Returns the value of the green channel.
int Color::getBlue( ) const{
    return blue;
} //Returns the value of the blue channel.

int Color::getChannel( const int& channel ) const{
    if (channel == 0){
        return red;
    }
    else if (channel == 1){
        return green;
    }
    else if (channel == 2){
        return blue;
    }
    else{
        return -1;
    }
} //Returns the value of the channelth channel. 0 == red, 1 == green, 2 == blue. Returns -1 if the channel is out of range.

void Color::setRed( const int& value ){
    if (value >= 0){
        red = value;
    }
} //Changes the red channel to value. If value is less than 0, do not make any changes.

void Color::setGreen( const int& value ){
    if (value >= 0){
        green = value;
    }
} //Changes the green channel to value. If value is less than 0, do not make any changes.

void Color::setBlue( const int& value ){
    if (value >= 0){
        blue = value;
    }
} //Changes the blue channel to value. If value is less than 0, do not make any changes.

void Color::setChannel( const int& channel, const int& value ){
    if (value < 0){
        return;
    }
    if (channel == 0){
        red = value;
    }
    else if (channel == 1){
        green = value;
    }
    else if (channel == 2){
        blue = value;
    }
} //Changes the channelth channel to value. If value is less than 0, do not make any changes. 0 == red, 1 == green, 2 == blue. Does not make changes if channel is out of range.

void Color::invert( const int& max_color_value ){
    if (max_color_value < red || max_color_value < green || max_color_value < blue){
        return;
    }
        red = max_color_value - red;
        green = max_color_value - green;
        blue = max_color_value - blue;
} //Inverts the red, green and blue channels, using max_color_value. If max_color_value is less than any of the current color channels (red, green or blue), then make no changes. The inversion is completed by subtracting the current value from max_color_value. For example: red = max_color_value - red. This only makes sense if red is <= max_color_value. That’s why we make no changes if any channel (red, green or blue) is larger than max_color_value.

bool Color::operator==( const Color& rhs ) const{
    return (red==rhs.red && green==rhs.green && blue==rhs.blue);
} //Returns true if *this and rhs have the same color values. Otherwise, returns false.


std::ostream& operator<<( std::ostream& os, const Color& color ){
    os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
    return os;
}

ColorTable::ColorTable( const int& num_color ){
    Colors.resize(num_color);
} //Sizes the Color collection to num_color items.

int ColorTable::getNumberOfColors( ) const{
    return Colors.size();
} //Returns the number of Colors stored.

void ColorTable::setNumberOfColors( const int& num_color ){
    Colors.resize(num_color);
} 
//Resizes the collection to hold num_color items. Previous Color contents may or may not be preserved.

const Color& ColorTable::operator[](const int& i) const {
    static Color error_color(-1, -1, -1);

    if (i < 0 || i >= Colors.size()) {
        return error_color;
    }

    return Colors[i];
}
   //Returns the ith Color in the collection. If i is out of range, returns a static memory Color object with all three channels set to -1. See an example below.
Color& ColorTable::operator[]( const int& i ){
    if (i < 0 || i >= (int) Colors.size()) {
        static Color error_color(-1,-1,-1);
        error_color = Color(-1,-1,-1);
        return error_color;
    }
    return Colors[i];
}
 //Returns the ith Color in the collection. If i is out of range, returns a static memory Color object with all three channels set to -1.

void ColorTable::setRandomColor( const int& max_color_value, const int& position ){
    if (max_color_value < 0){
        return;
    }
    if (position < 0 || position >= Colors.size()){
        return;
    }

    int r = rand() % (max_color_value + 1);
    int g = rand() % (max_color_value + 1);
    int b = rand() % (max_color_value + 1);

    Colors[position].setChannel(0,r);
    Colors[position].setChannel(1,g);
    Colors[position].setChannel(2,b);
} //Assigns the positionth color random values for all three channels. The random values are between 0 and max_color_value, inclusive. If position is out of range, no change is made. If max_color_value is less than 0, no change is made. This method should NOT use std::srand() Add std::srand(std::time(0)); to main() of ppm_menu.cpp.

double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const{
    double slope = ((y2-y1)/(x2-x1));
    return slope;
} //Calculates a slope from point 1 to point 2, using “rise-over-run” calculation. Be sure to use floating point division operation.

double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const {
    return y1 + slope * (x - x1);
} //Calculate the y-value along the gradient from point (x1,y1) to the point at position x.

void ColorTable::insertGradient(const Color& color1, const Color& color2, const int& position1, const int& position2) {
    if (position1 < 0 || position2 < 0) {
        return;
    }
    if (position1 >= Colors.size() || position2 >= Colors.size()) {
        return;
    }
    if (position1 >= position2) {
        return;
    }

    double redSlope = gradientSlope(color1.getChannel(0), color2.getChannel(0),
                                    position1, position2);
    double greenSlope = gradientSlope(color1.getChannel(1), color2.getChannel(1),
                                      position1, position2);
    double blueSlope = gradientSlope(color1.getChannel(2), color2.getChannel(2),
                                     position1, position2);

    for (int i = position1; i <= position2; i++) {
        int red = gradientValue(color1.getChannel(0), redSlope, i, position1);
        int green = gradientValue(color1.getChannel(1), greenSlope, i, position1);
        int blue = gradientValue(color1.getChannel(2), blueSlope, i, position1);

        Colors[i].setChannel(0, red);
        Colors[i].setChannel(1, green);
        Colors[i].setChannel(2, blue);
    }
}
 //Change the colors from position1 to position2, inclusive, to be gradients from color1 to color2. If position1 is not less than position2, no change is made. If either position is out of range, no change is made. Should use the gradientSlope() and gradientValue() methods.
int ColorTable::getMaxChannelValue() const {
    int maxVal = 0;

    for (int i = 0; i < Colors.size(); i++) {
        if (Colors[i].getChannel(0) > maxVal)
            maxVal = Colors[i].getChannel(0);

        if (Colors[i].getChannel(1) > maxVal)
            maxVal = Colors[i].getChannel(1);

        if (Colors[i].getChannel(2) > maxVal)
            maxVal = Colors[i].getChannel(2);
    }

    return maxVal;
}//Finds the largest value of any red, greeen, or blue value in any color in the table.
