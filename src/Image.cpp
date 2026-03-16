#include "Image.h"


Image::Image() {
    width = 0;
    height = 0;
    data.resize(width * height * 3);
}

Image::Image( const int& h, const int& w ) {
    if (w >= 0 && h >= 0) {
        width = w;
        height = h;
        data.resize(width * height * 3);
}
    else {
        width = 0;
        height = 0;
        data.resize(0);
    }
    }

int Image::getHeight() const {
     return height;
}

int Image::getWidth() const {
    return width;
}

bool Image::indexValid( const int& row, const int& column, const int& channel ) const {
    return (row >= 0 && row < height && column >= 0 && column < width && channel >=0 && channel < 3);
}

int Image::index( const int& row, const int& column, const int& channel ) const {
    return (row * width * 3 + column * 3) + channel;
}

int Image::getChannel( const int& row, const int& column, const int& channel ) const {
    if (!indexValid(row,column,channel)) {
        return -1;
    }
    else {
        return data[index(row,column,channel)];
    }
}
void Image::setHeight(const int& h) {
    if (h > 0) {
        height = h;
        if (width > 0 && height > 0) {
            data.resize(width * height * 3);
        }
    }
}

void Image::setWidth(const int& w) {
    if (w > 0) {
        width = w;
        if (width > 0 && height > 0) {
            data.resize(width * height * 3);
        }
    }
}

void Image::heightwidth(const int& h, const int& w) {
    if (h >= 0 && w >= 0) {
        height = h;
        width = w;
        data.resize(width * height * 3, 0); // initialize all pixels to 0
    }
}

void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
    if (indexValid(row,column,channel)) {
        data[index(row,column,channel)] = value;
    }
}