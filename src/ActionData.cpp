#include "ActionData.h"
#include "NumberGrid.h"

ActionData::ActionData(std::istream& is, std::ostream& os)
: input(is), output(os), Done(false), numberGrid(0) {}

std::istream& ActionData::getIS(){
    return input;
}

std::ostream& ActionData::getOS() {
    return output;
}

PPM& ActionData::getInputImage1() {
    return inputimage1;
}

PPM& ActionData::getInputImage2() {
    return inputimage2;
}

PPM& ActionData::getOutputImage() {
    return outputimage;
}

bool ActionData::getDone() const{
    return Done;
}

void ActionData::setDone() {
    Done=true;
}

ActionData::~ActionData(){
    delete numberGrid;

}

NumberGrid& ActionData::getGrid(){
    return *numberGrid;
}

void ActionData::setGrid(NumberGrid *grid){
    if (grid != 0){
        delete numberGrid;
    }
    *numberGrid = *grid;
}