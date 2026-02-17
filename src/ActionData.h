#pragma once
#include <iostream>
#include "PPM.h"
#include "Image.h"




class ActionData {
public:
    ActionData(std::istream& is, std::ostream& os);
    std::istream& getIS();
    std::ostream& getOS();
    PPM& getInputImage1();
    PPM& getInputImage2();
    PPM& getOutputImage();
    bool getDone() const;
    void setDone();
private:
    std::istream& input;
    std::ostream& output;
    PPM inputimage1;
    PPM inputimage2;
    PPM outputimage;
    bool Done;



};