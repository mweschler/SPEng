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
			//cout << "inside instance\n";
			if(instance == NULL){
				//cout << "inside instance is NULL\n";
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
		int Logger::writeToLog(string message)
		{
			int result;

			if(dataLogExists)
			{
				time_t theTime;
				struct tm aTime;
				time ( &theTime );
				localtime_s(&aTime, &theTime);
		
				
				int day = aTime.tm_mday;
				int month = aTime.tm_mon + 1; 
				int year = aTime.tm_year + 1900; 
				int hours = aTime.tm_hour;
				int minutes = aTime.tm_min;
				int seconds = aTime.tm_sec;
				
						
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
				//hours = 0;

				

				//os << hours;
				//cout << os.str();
				//cout << "THE Hours before everything " + hoursString + "\n";
				//os.str("");

				
				//if it's a digit from 1 - 9, add a 0 before them.
				if(hours%12 < 10)
				{
					//if it is 12 noon or midnight, hours is 12.
					if(hours%12 == 0)
					{
						//hours = 12;
						int shours = 12;
						os << shours;
						hoursString = os.str();
						
					}
					else
					{
					
						int shours = hours%12;
						os << "0" << shours;
						hoursString = os.str();
					}
					
				}
				else
				{
					if(hours%12 == 0)
					{
						hours = 12;
					}
					int shours = hours%12;
					
					os << shours;
					
				   cout << os.str();
					hoursString = os.str();
				}
				os.str("");

				if(minutes < 10)
				{
					
					os << "0" << minutes;
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
					//os << "0" + seconds;
					os << "0" << seconds;
					secondsString = os.str();
				}
				else
				{
					os << seconds;
					secondsString = os.str();
				}
				os.str("");

				if(hours < 12)
				{
					amORpm = "A.M.";
				}
				else if(hours > 11)
				{
					amORpm = "P.M.";
				}
				//cout << "the month\n";
				//cout << month;
			
				switch(month)
				{
					case 1:  monthName  = "January"; break;
					case 2:  monthName  = "February"; break;
					case 3:  monthName  = "March"; break;
					case 4:  monthName  = "April"; break;
					case 5:  monthName  = "May"; break;
					case 6:  monthName  = "June"; break;
					case 7:  monthName  = "July"; break;
					case 8:  monthName  = "August"; break;
					case 9:  monthName  = "September"; break;
					case 10: monthName  = "October"; break;
					case 11: monthName  = "November"; break;
					case 12: monthName  = "December"; break;
				}

				/*
				cout << "\nThe Month " + monthName + "\n";
				cout << "THE Hours " + hoursString + "\n";
				cout << "The minutes " + minutesString + "\n";
				cout << "the seconds " + secondsString + "\n";
				*/

				stringstream osa;
				osa << "[" << monthName << " " << day << ", " << year << " - " << hoursString << ":" <<  minutesString << "::" << secondsString << " " << amORpm  << "]  ";
				string dateStats = osa.str();
				dataLog.open(dataLogName, ios_base::app);
				//cout << message;
				dataLog << dateStats << message << endl;
				//cout << "Message has been written\n";
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
			//cout << "Inside createLog\n";
			int result;
			if(!dataLogExists)
			{	    
				dataLog.open(dataLogName);
				dataLog.close();
				//cout << "Log has been created.\n";
				dataLogExists = true;
				result = 1;
			}
			else
			{
				//cout << "Log is already created\n" ;
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
				//cout << "Data Log does not exist, failed to delete";
				result = 0;
			}
			else
			{		
				//cout << "Data Log successfully removed log";
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