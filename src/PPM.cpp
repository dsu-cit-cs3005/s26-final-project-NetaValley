#include "PPM.h"

PPM::PPM()
: max_color_value(1) {}

PPM::PPM(const int& height, const int& width)
: max_color_value(1) {
    setWidth(width);
    setHeight(height);
}


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

void PPM::readStream(std::istream& is) {

    std::string magic;
    int width;
    int height;
    int max_color_value;

    is >> magic;
    is >> width >> height;
    is >> max_color_value;

    if (magic != "P6") {
        return; 
    }

    setWidth(width);
    setHeight(height);
    setMaxColorValue(max_color_value);

    is.get();

    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {

            unsigned char r;
            unsigned char g;
            unsigned char b;

            is.read(reinterpret_cast<char*>(&r), 1);
            is.read(reinterpret_cast<char*>(&g), 1);
            is.read(reinterpret_cast<char*>(&b), 1);

            setPixel(row, column, r, g, b);
        }
    }
}

int PPM::getPixel() const {
    int pixels =  getHeight() * getWidth();
    return pixels;
}

bool PPM::operator==( const PPM& rhs ) const {
    int pixels = getPixel();
    int pixelsrhs = rhs.getPixel();
    return pixels == pixelsrhs;
}

bool PPM::operator!=( const PPM& rhs ) const{
    int pixels = getPixel();
    int pixelsrhs = rhs.getPixel();
    return pixels != pixelsrhs;
}

bool PPM::operator<( const PPM& rhs ) const{
    int pixels = getPixel();
    int pixelsrhs = rhs.getPixel();
    return pixels < pixelsrhs;
}

bool PPM::operator<=( const PPM& rhs ) const{
    int pixels = getPixel();
    int pixelsrhs = rhs.getPixel();
    return pixels <= pixelsrhs;
}

bool PPM::operator>( const PPM& rhs ) const{
    int pixels = getPixel();
    int pixelsrhs = rhs.getPixel();
    return pixels > pixelsrhs;
}

bool PPM::operator>=( const PPM& rhs ) const{
    int pixels = getPixel();
    int pixelsrhs = rhs.getPixel();
    return pixels >= pixelsrhs;
}

PPM& PPM::operator+=( const PPM& rhs ){
    for (int row = 0; row < getHeight(); ++row){
        for (int column = 0; column < getWidth(); ++column){
            for (int channel = 0; channel < 3; ++channel){

            int sum = getChannel(row,column,channel) + rhs.getChannel(row,column,channel);

            if (sum > getMaxColorValue()) {
                sum = getMaxColorValue();
            }
            setChannel(row,column,channel,sum);
        }
    }
}
    return *this;
}

PPM& PPM::operator-=( const PPM& rhs ){
    for (int row = 0; row < getHeight(); ++row){
        for (int column = 0; column < getWidth(); ++column){
            for (int channel = 0; channel < 3; ++channel){

            int sum = getChannel(row,column,channel) - rhs.getChannel(row,column,channel);

            if (sum < 0) {
                sum = 0;
            }
            setChannel(row,column,channel,sum);
        }
    }
}
    return *this;
}

PPM& PPM::operator*=( const double& rhs ){
    for (int row = 0; row < getHeight(); ++row){
        for (int column = 0; column < getWidth(); ++column){
            for (int channel = 0; channel < 3; ++channel){

            int sum = getChannel(row,column,channel) * rhs;

            if (sum > getMaxColorValue()) {
                sum = getMaxColorValue();
            }
            if (sum < 0) {
                sum = 0;
            }

            setChannel(row,column,channel,sum);
        }
    }
}
    return *this;
}

PPM& PPM::operator/=( const double& rhs ){
    for (int row = 0; row < getHeight(); ++row){
        for (int column = 0; column < getWidth(); ++column){
            for (int channel = 0; channel < 3; ++channel){

            int sum = getChannel(row,column,channel) / rhs;

            if (sum > getMaxColorValue()) {
                sum = getMaxColorValue();
            }
            if (sum < 0) {
                sum = 0;
            }

            setChannel(row,column,channel,sum);
        }
    }
}
    return *this;
}

PPM PPM::operator+( const PPM& rhs ) const{
    PPM object(*this);
    object += rhs;
    return object;
}

PPM PPM::operator-( const PPM& rhs ) const{
    PPM object(*this);
    object -= rhs;
    return object;
}

PPM PPM::operator*( const double& rhs ) const{
    PPM object(*this);
    object *= rhs;
    return object;
}

PPM PPM::operator/( const double& rhs ) const{
    PPM object(*this);
    object /= rhs;
    return object;
}
