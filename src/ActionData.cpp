#include "ActionData.h"
#include "NumberGrid.h"

ActionData::ActionData(std::istream& is, std::ostream& os)
: input(is), output(os), Done(false), NumberGrid(0) {}

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

~ActionData(){

}

NumberGrid& getGrid(){
    return *NumberGrid;
}

void setGrid(NumberGrid *grid){
    if (NumberGrid != 0){
        delete NumberGrid;
    }
    NumberGrid = grid;
}