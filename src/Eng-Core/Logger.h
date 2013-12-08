#pragma once
#include <string>
#include <fstream>
using namespace std;


/*! Logger keeps track of a data log and allows the user to access it, create one, and write to one.*/
class Logger{
	public:
		/*! Provides the user with the singleton Logger object.
		/return pointer to the Logger created.
		*/
		static Logger* Instance();	
		
		/*! Starts up the Logger, only has to be called one time.
		/return true upon successful initialization
		*/
		bool initialize();

		/*! Allows user to write a message onto the data log.
		/param the message the user wants to write to the log.
		/return an int returning 1 if successfully written or 0 if message was not successfully written.
		*/
		int writeToLog(std::string message);
		
		/*! Allows the user to remove the log from file
		/return returns 1 upon successful conclusion and 0 on failure to delete log.
		*/
		int deleteLog();

		/*! Writes final line of logger indicating termination of logger activity.*/
		void shutdown();
		
		/*! Gets the name of the data log
		/return the name of the data log
		*/
		string getDataLogName();
		
		/*! Checks to see if a data log exists
		/return true if the data log has been created, false otherwise
		*/
		bool getDataLogExists();

	private:
		
		/*! Creates the data log
		/return returns 1 upon successful log creation, 0 otherwise
		*/
		int createLog();

		/*! variable containing the name of the data log */
		string dataLogName;

		/*! boolean stating whether or not a data log exists */
		bool dataLogExists;
		
		/*!	string that will contain the message user wishes to place into Logger*/
		string dataMessage;
		
		/*! ofstream data log will be using	*/
		ofstream dataLog;

		static Logger* instance;
		Logger();
		Logger(Logger const&);
		Logger& operator=(Logger const&);



};