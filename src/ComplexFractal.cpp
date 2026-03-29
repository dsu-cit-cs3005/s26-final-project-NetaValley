#include "ComplexFractal.h"
#include <cmath>


ComplexFractal::ComplexFractal()
: NumberGrid(301,201), min_x(-1.5), max_x(1.5), min_y(-1), max_y(1), delta_x(0.01), delta_y(0.01)
{}

ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
: NumberGrid(height,width), min_x(min_x), max_x(max_x), min_y(min_y), max_y(max_y), delta_x(0.0), delta_y(0.0){
setDeltas(calculateDeltaX(), calculateDeltaY());
}


ComplexFractal::~ComplexFractal( )
{}

double ComplexFractal::getMinX( ) const{
    return min_x;
}

double ComplexFractal::getMaxX( ) const{
    return max_x;
}

double ComplexFractal::getMinY( ) const{
    return min_y;
}

double ComplexFractal::getMaxY( ) const{
    return max_y;
}

void ComplexFractal::setGridSize( const int& height, const int& width ){
    if (height >= 2 && width >= 2){
        int tempheight = getHeight();
        int tempwidth = getWidth();
        NumberGrid::setGridSize(height, width);
        if (tempheight != getHeight() || tempwidth != getWidth()) {
            setDeltas(calculateDeltaX(), calculateDeltaY());
        }
    }
}

void ComplexFractal::setPlaneSize(const double& min_x, const double& max_x,
                                  const double& min_y, const double& max_y) {
    if ((min_x >= -2.0 && min_x <= 2.0) &&
        (max_x >= -2.0 && max_x <= 2.0) &&
        (min_y >= -2.0 && min_y <= 2.0) &&
        (max_y >= -2.0 && max_y <= 2.0)) {

        double new_min_x = min_x;
        double new_max_x = max_x;
        double new_min_y = min_y;
        double new_max_y = max_y;

        if (new_min_x > new_max_x) {
            double temp = new_min_x;
            new_min_x = new_max_x;
            new_max_x = temp;
        }

        if (new_min_y > new_max_y) {
            double temp = new_min_y;
            new_min_y = new_max_y;
            new_max_y = temp;
        }

        if (new_min_x == new_max_x || new_min_y == new_max_y) {
            return;
        }

        bool changed = false;

        if (this->min_x != new_min_x) {
            this->min_x = new_min_x;
            changed = true;
        }
        if (this->max_x != new_max_x) {
            this->max_x = new_max_x;
            changed = true;
        }
        if (this->min_y != new_min_y) {
            this->min_y = new_min_y;
            changed = true;
        }
        if (this->max_y != new_max_y) {
            this->max_y = new_max_y;
            changed = true;
        }

        if (changed) {
            setDeltas(calculateDeltaX(), calculateDeltaY());
        }
    }
}

double ComplexFractal::getDeltaX( ) const{
    return delta_x;
}

double ComplexFractal::getDeltaY( ) const{
    return delta_y;
}

void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y ){
    if (delta_x > 0 && delta_y > 0){
        this->delta_x = delta_x;
        this->delta_y = delta_y;
    }
}

double ComplexFractal::calculateDeltaY( ) const{
    return ((max_y - min_y) / (getHeight() -1));
}


double ComplexFractal::calculateDeltaX( ) const{
    return ((max_x - min_x) / (getWidth() -1));
}

double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column ) const{
    if (column < 0 || column >= getWidth()){
        return 0;
    }
    return (min_x + column * delta_x);
}


double ComplexFractal::calculatePlaneYFromPixelRow( const int& row ) const{
    if (row < 0 || row >= getHeight()){
        return 0;
    }
    return (max_y - row * delta_y);
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const{
    if (( row < 0 || row >= getHeight()) || (column < 0 || column >= getWidth())){
        x = 0;
        y = 0;
    }
    else {
    x = calculatePlaneXFromPixelColumn(column);
    y = calculatePlaneYFromPixelRow(row);
    }
}
int ComplexFractal::calculateNumber( const int& row, const int& column ) const{
    double x;
    double y;
    if (indexValid(row,column)){
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
        int value = std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y));
        return value;
    }
    else {
        return -1;
    }
}
