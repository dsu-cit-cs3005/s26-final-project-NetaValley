#include "MandelbrotSet.h"
#include <cmath>

MandelbrotSet::MandelbrotSet()
    : ComplexFractal()
{}

MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y)
{}

MandelbrotSet::~MandelbrotSet( )
{}

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const{
    x1 = (x0*x0 - y0*y0 + a);
    y1 = (2*x0*y0 + b);
}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const{
    double x = a;
    double y = b;
    if (sqrt(a*a + b*b) > 2.0){
        return 0;
    } 
    double x_next;
    double y_next;
    int count=0;
    int max_escape_count = this->getMaxNumber();
    for (int i = 0; i < max_escape_count; i++){
        calculateNextPoint(x,y,a,b,x_next,y_next);
        x = x_next;
        y = y_next;
        double d = (sqrt(x*x + y*y));
        count++;
        if (d > 2.0){
            return count;
        }
    }
    return max_escape_count;
}

int MandelbrotSet::calculateNumber( const int& row, const int& column ) const{
    if (row < 0 || row >= getHeight() || column < 0 || column >= getWidth()) {
        return -1;
    }

    double x0;
    double y0;
    calculatePlaneCoordinatesFromPixelCoordinates(row,column,x0,y0);
    return calculatePlaneEscapeCount(x0,y0);
}