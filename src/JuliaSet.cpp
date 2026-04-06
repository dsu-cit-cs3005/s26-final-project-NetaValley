#include "JuliaSet.h"
#include <cmath>



JuliaSet::JuliaSet( )
: ComplexFractal(){ 
    a = -0.650492;
    b = -0.478235;
    setMaxNumber(255);
}

JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b )
: ComplexFractal(height, width, min_x, max_x, min_y, max_y), a(a), b(b)
{}

JuliaSet::~JuliaSet( )
{}

double JuliaSet::getA( ) const{
    return a;
}

double JuliaSet::getB( ) const{
    return b;
}

void JuliaSet::setParameters( const double& a, const double& b ){
    if ((a < -2.0) || (a > 2.0) || (b < -2.0) || (b > 2.0)){
        return;
    }
    this->a = a;
    this->b = b;
}

void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const{
    x1 = (x0*x0 - y0*y0 + a);
    y1 = (2*x0*y0 + b);
}

int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const{
    double x = x0;
    double y = y0;
    int count = 0;
    for (int i = 0; i < getMaxNumber(); i++){
        double d = sqrt(x*x + y*y);
        if (d > 2){
            break;
        }
        double next_x;
        double next_y;
        calculateNextPoint(x, y, next_x, next_y);
        x = next_x;
        y = next_y;
        count++;
    }
    return count;
}

int JuliaSet::calculateNumber( const int& row, const int& column ) const {
    if (row < 0 || row >= getHeight() || column < 0 || column >= getWidth()) {
        return -1;
    }

    double x0;
    double y0;
    calculatePlaneCoordinatesFromPixelCoordinates(row, column, x0, y0);

    return calculatePlaneEscapeCount(x0, y0);
}