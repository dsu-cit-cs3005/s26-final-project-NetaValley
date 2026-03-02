#pragma once
#include "Image.h"
#include "ActionData.h"
#include "PPM.h"
#include "MenuData.h"
#include <iostream>
#include <string>


// Function declarations

std::string getString( ActionData& action_data, const std::string& prompt );
int getInteger( ActionData& action_data, const std::string& prompt );
double getDouble( ActionData& action_data, const std::string& prompt );

std::string getChoice( ActionData& action_data );
void commentLine( ActionData& action_data );
void quit(ActionData& action_data);

int askQuestions3(ActionData& action_data);
int assignment1(std::istream& is, std::ostream& os);
void drawAsciiImage( ActionData& action_data );
void diagonalQuadPattern( ActionData& action_data );
int assignment2(std::istream& is, std::ostream& os);

void writeUserImage( ActionData& action_data );
void stripedDiagonalPattern( ActionData& action_data );
int assignment3( std::istream& is, std::ostream& os );

void setSize( ActionData& action_data );
void setMaxColorValue( ActionData& action_data );
void setChannel( ActionData& action_data );
void setPixel( ActionData& action_data );
void clearAll( ActionData& action_data );

void copyImage(ActionData& action_data);
void readUserImage1( ActionData& action_data );

void showMenu( MenuData& menu_data, ActionData& action_data );
void takeAction(const std::string& choice, MenuData& menu_data, ActionData& action_data);
void configureMenu( MenuData& menu_data );
int imageMenu(std::istream& is, std::ostream& os);

void plusEquals( ActionData& action_data );
void minusEquals( ActionData& action_data );
void timesEquals( ActionData& action_data );
void divideEquals( ActionData& action_data );
void plus( ActionData& action_data );
void minus( ActionData& action_data );
void times( ActionData& action_data );
void divide( ActionData& action_data );

void readUserImage2( ActionData& action_data );


void grayFromRed(ActionData& action_data); 
void grayFromGreen(ActionData& action_data);
void grayFromBlue(ActionData& action_data); 
void grayFromLinearColorimetric(ActionData& action_data); 


void drawCircle(ActionData& action_data);
void drawBox(ActionData& action_data);