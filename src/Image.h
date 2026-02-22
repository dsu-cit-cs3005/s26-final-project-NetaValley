#ifndef IMAGE_H //avoids creating the same file twice
#define IMAGE_H
#include <vector> //includes vector
#include <iostream>


class Image {
private: 
    int width;
    int height; 
    std::vector<int> data; //store all pixel values

public:
    Image();  // default constructor
    Image(const int& height, const int& width); // parameterized constructor

    int getHeight() const;
    int getWidth() const;
    
    bool indexValid(const int& row, const int& column, const int& channel) const;
    int index(const int& row, const int& column, const int& channel) const;
    
    int getChannel(const int& row, const int& column, const int& channel) const;
    void setChannel(const int& row, const int& column, const int& channel, const int& value);
    
    void setHeight(const int& height);
    void setWidth(const int& width);

};





#endif