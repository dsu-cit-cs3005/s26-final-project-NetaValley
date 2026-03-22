#include "ActionData.h"
#include "NumberGrid.h"

ActionData::ActionData(std::istream& is, std::ostream& os)
: colorTable(16),input(is), output(os), Done(false), numberGrid(0)
{
    Color start(0, 255, 0);
    Color end(255, 0, 255);

    colorTable.insertGradient(start, end, 0, 15);
}

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
    if (numberGrid != nullptr){
        delete numberGrid;
    }
    numberGrid = grid;
}
ColorTable& ActionData::getTable(){
    return colorTable;
}