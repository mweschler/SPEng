#include "Logger.h"
#include <iostream>
#include <fstream>

		//Basic constructor for Logger
		Logger::Logger(){
			dataLogName = "Data_Log.txt";
			dataLogExists = true;
		}

		//default initialize method
	    bool Logger::initialize(){

			return true;
		}

		//Future site of how the message will be written to the file.
		int Logger::writeToLog(std::string message){
			
			return 0;
		}

		//Creates the file for the person.
		int Logger::createLog(){
			
			std::cout << "potato salade pantesomppe";
			return 0;
		}

		//Delete, or clears the log. 
		int Logger::deleteLog(){

			return 0;
		}

		//default shutdown method.
		void Logger::shutdown(){

			
		}


