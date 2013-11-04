#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <ctime>
#include <sstream> 

using namespace std;

Logger* Logger::instance = NULL;

		//Constructor for Logger
		Logger::Logger()
		{
			dataLogName = ".\\Data_Log.txt";
			dataLogExists = false;
		}

		Logger* Logger::Instance()
		{
			cout << "inside instance\n";
			if(instance == NULL){
				cout << "inside instance is NULL\n";
				instance = new Logger();
			}
			return instance;
		}

		string Logger::getDataLogName()
		{
			return dataLogName;
		}

		bool Logger::getDataLogExists()
		{
			return dataLogExists;
		}

		//default initialize method
	    bool Logger::initialize()
		{
	
			ifstream infile(dataLogName);
			if(!infile.good())
			{
				createLog();
			}
			dataLogExists = true;
				/*{
				cout << "inside initialize > infile is found\n";
				dataLogExists = true;
			}
			else
			{
				cout << "inside initialize > infile is not found\n";
				dataLogExists = false;
				createLog();
				cout << "log has been created inside initialize\n";
			}*/
			writeToLog("Log Started");
				return true;
		}
		
		//Future site of how the message will be written to the file.
		int Logger::writeToLog(string message){

			int result;
			if(dataLogExists)
			{
				time_t theTime = time(NULL);
				struct tm *aTime = localtime(&theTime);

				int day = aTime->tm_mday;
				int month = aTime->tm_mon + 1; 
				int year = aTime->tm_year + 1900; 
				int hours = aTime->tm_hour;
				int minutes = aTime-> tm_min;
				int seconds = aTime-> tm_sec;
				string amORpm = "";
				string monthName = "";
				string hoursString = "";
				string minutesString = "";
				string secondsString = "";
				stringstream os;
				//os << hours;
				//cout << os.str();
				//cout << "THE Hours before everything " + hoursString + "\n";
				//os.str("");
				
				if(hours%12 < 10)
				{
					if(hours%12 == 0)
					{
						hours = 12;
						os << hours;
						hoursString = os.str();
						
					}
					else
					{
						os << "0" + hours;
						hoursString = os.str();
					}
					
				}
				else
				{
					if(hours%12 == 0)
					{
						hours = 12;
					}
					hours = hours%12;
					os << "\n new hours " + hours;
					
				   cout << os.str();
					hoursString = os.str();
				}
				os.str("");

				if(minutes < 10)
				{
					os << "0" + minutes;
					minutesString = os.str();
				}
				else
				{
					os << minutes;
					minutesString = os.str();
				}
				os.str("");

				if(seconds < 10)
				{
					os << "0" + seconds;
					secondsString = os.str();
				}
				else
				{
					os << seconds;
					secondsString = os.str();
				}
				os.str("");

				if(hours/12 == 0 || hours == 12)
				{
					amORpm = "A.M.";
				}
				else
				{
					amORpm = "P.M.";
				}

				switch(month)
				{
					case 1:  monthName  = "January";
					case 2:  monthName  = "February";
					case 3:  monthName  = "March";
					case 4:  monthName  = "April";
					case 5:  monthName  = "May";
					case 6:  monthName  = "June";
					case 7:  monthName  = "July";
					case 8:  monthName  = "August";
					case 9:  monthName  = "September";
					case 10: monthName  = "October";
					case 11: monthName  = "November";
					case 12: monthName  = "December";
				}
				/*
				cout << "THE Hours " + hoursString + "\n";
				cout << "The minutes " + minutesString + "\n";
				cout << "the seconds " + secondsString + "\n";*/

				stringstream osa;
				osa << "[" << monthName << " " << day << ", " << year << " - " << hoursString << ":" <<  minutesString << "::" << secondsString << " " << amORpm  << "]  ";
				string dateStats = osa.str();
				dataLog.open(dataLogName, ios_base::app);
				dataLog << dateStats << message << endl;
				cout << "Message has been written\n";
				dataLog.close();

				result = 1;
			}
			else
			{
				cout << "Failed to write to log, a data log has not been created yet.\n";
				result = 0;
			}
			
			return result;
		}

		//Creates the file for the person.
		int Logger::createLog(){
			cout << "Inside createLog\n";
			int result;
			if(!dataLogExists)
			{	    
				dataLog.open(dataLogName);
				dataLog.close();
				cout << "Log has been created.\n";
				dataLogExists = true;
				result = 1;
			}
			else
			{
				cout << "Log is already created\n" ;
				result = 0;
			}
			return result;
		}

		//Delete, or clears the log. 
		int Logger::deleteLog()
		{
			int result;

			if(!dataLogExists)
			{
				cout << "Data Log does not exist, failed to delete";
				result = 0;
			}
			else
			{		
				cout << "Data Log successfully removed log";
				remove(dataLogName.c_str());	
				result = 1;
			}
			instance = NULL;

			return result;
		}

		//default shutdown method.
		void Logger::shutdown(){

			writeToLog("Log End");

			
			
		}