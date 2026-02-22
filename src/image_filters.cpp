#include "image_menu.h"
#include "PPM.h"
#include "ActionData.h"

void plusEquals( ActionData& action_data ){
    action_data.getInputImage1() += action_data.getInputImage2();
}
void minusEquals( ActionData& action_data ){
    action_data.getInputImage1() -= action_data.getInputImage2();
}
void timesEquals( ActionData& action_data ){
    double factor = getDouble(action_data, "Factor? ");
    action_data.getInputImage1() *= factor;
}
void divideEquals( ActionData& action_data ){
    double factor = getDouble(action_data, "Factor? ");
    action_data.getInputImage1() /= factor;
}
void plus( ActionData& action_data ){
    action_data.getOutputImage() = action_data.getInputImage1() + action_data.getInputImage2();
}
void minus( ActionData& action_data ){
    action_data.getOutputImage() = action_data.getInputImage1() - action_data.getInputImage2();
}
void times( ActionData& action_data ){
    double factor = getDouble(action_data, "Factor? ");
    action_data.getOutputImage() = action_data.getInputImage1() * factor;
}
void divide( ActionData& action_data ){
    double factor = getDouble(action_data, "Factor? ");
    action_data.getOutputImage() = action_data.getInputImage1() / factor;
}