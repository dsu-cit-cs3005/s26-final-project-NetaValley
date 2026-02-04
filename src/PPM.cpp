#include "PPM.h"

PPM::PPM()
: max_color_value(1) {}

PPM::PPM(const int& height, const int& width)
: max_color_value(1) {
    setWidth(width);
    setHeight(height);
}

// PPM::PPM() 
// : max_color_value(1) { //member initiazer list
//     image Image;
// }



// PPM::PPM( const int& height, const int& width )
// : max_color_value(1) {
//     Image image(height, width);
// }

int PPM::getMaxColorValue() const {
    return max_color_value;
}

bool PPM::valueValid(const int& value) const {
    if (value >=0) {
        if (value <= max_color_value) {
            return true;
        }
    }
    return false;
}

void PPM::setMaxColorValue(const int& max_color_value) {
    if (1 <= max_color_value && max_color_value <= 255) {
        this->max_color_value = max_color_value;
    }
}

void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value) {
    if (valueValid(value)) {
        Image::setChannel(row,column,channel,value);
    }
}

void PPM::setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue) {
    setChannel(row,column, 0, red);
    setChannel(row,column, 1, green);
    setChannel(row,column, 2, blue);
    return;
}

void PPM::writeStream(std::ostream& os) const {
    int width = getWidth();
    int height = getHeight();
    int max_color_value = getMaxColorValue();

    os << "P6 " << width << " " << height << " " << max_color_value << "\n";

    for (int row = 0; row < height; row++) {
        for (int column=0; column < width; column++) {
            int red = getChannel(row,column,0);
            int green = getChannel(row,column,1);
            int blue = getChannel(row,column,2);

            unsigned char redChar = static_cast<unsigned char> (red);
            os.write(reinterpret_cast<char*>(&redChar),1);

            unsigned char greenChar = static_cast<unsigned char> (green);
            os.write(reinterpret_cast<char*>(&greenChar),1);

            unsigned char blueChar = static_cast<unsigned char> (blue);
            os.write(reinterpret_cast<char*>(&blueChar),1);            
        }
    }
}