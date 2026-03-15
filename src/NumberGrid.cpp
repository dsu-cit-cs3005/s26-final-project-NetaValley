#include "NumberGrid.h"

    NumberGrid::NumberGrid()
    : max_value(255), height(300), width(400),  data(300 * 400, 0) {}

    NumberGrid::NumberGrid( const int& h, const int& w )
    : max_value(255), height(h), width(w) {
        data.resize(width * height, 0);
    }

    NumberGrid::~NumberGrid() {}


    int NumberGrid::getHeight( ) const{
        return height;
    }

    int NumberGrid::getWidth( ) const{
        return width;
    }

    int NumberGrid::getMaxNumber( ) const {
        return max_value;
    }
//hello
    void NumberGrid::setGridSize( const int& height, const int& width ){
        if (height >= 2 && width >= 2) {
            this->height = height;
            this->width = width;
            data.resize(width * height);
        }
    } 

    void NumberGrid::setMaxNumber( const int& number ){
        if (number >=0){
            this->max_value = number;
        }
    }


    const std::vector< int >& NumberGrid::getNumbers( ) const{
        return data;
    }

    int NumberGrid::index( const int& row, const int& column ) const{
        return (row*width+column);
    }

    bool NumberGrid::indexValid( const int& row, const int& column ) const{
        return (row >= 0 && row < height && column >= 0 && column < width);

    }
    bool NumberGrid::numberValid( const int& number ) const{
        return (number >= 0 && number <= max_value);

    }
    int NumberGrid::getNumber( const int& row, const int& column ) const{
        if (indexValid(row,column)){
            return data[index(row,column)];
        }
        return -1;
    }

    void NumberGrid::setNumber( const int& row, const int& column, const int& number ){
        if (indexValid(row,column)) {
            if (numberValid(number)) {
                data[index(row,column)] = number;
            }
        }
    }
    void NumberGrid::setPPM( PPM& ppm ) const{
        ppm.heightwidth(this->height, this->width);
        ppm.setMaxColorValue(63);
        for (int row=0;row < ppm.getHeight(); row++){
            for (int col=0;col < ppm.getWidth(); col++){
                if (getNumber(row,col) == 0 || (getNumber(row,col) % 8) == 4){
                    ppm.setPixel(row,col,0,0,0);
                }

                else if (getNumber(row,col) == this->max_value) {
                    ppm.setPixel(row,col,63,31,31);
                }
                else if ((getNumber(row,col)%8) == 0){
                    ppm.setPixel(row,col,63,63,63);
                }
                else if ((getNumber(row,col)%8) == 1){
                    ppm.setPixel(row,col,63,31,31);
                }
                else if ((getNumber(row,col)%8) == 2){
                    ppm.setPixel(row,col,63,63,31);
                }
                else if ((getNumber(row,col)%8) == 3){
                    ppm.setPixel(row,col,31,63,31);
                }
                else if ((getNumber(row,col)%8) == 5){
                    ppm.setPixel(row,col,31,63,63);
                }
                else if ((getNumber(row,col)%8) == 6){
                    ppm.setPixel(row,col,31,31,63);
                }
                else if ((getNumber(row,col)%8) == 7){
                    ppm.setPixel(row,col,63,31,63);
                }
            }
        }

    }