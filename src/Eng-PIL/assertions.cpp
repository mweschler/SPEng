#include <string>
#include <sstream>
#include <iostream>
#include "assertions.h"


void reportAssertion(const char *expression, const char *file, const long line){
	
	std::stringstream msgstream;
	msgstream <<"ASSERTION FAILURE!"<<std::endl<< "'"<<expression
		<<"' evaluated false."<<std::endl<<"File: "<<file<<" Line: "<<line;
	std::string message = msgstream.str();
	std::cout<<message<<std::endl;
	//GUI::showMessageBox(message, TEXT("Assertion Failure"));
}