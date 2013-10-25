#include <string>
#include <fstream>


//h file for logger class
class Logger{
	public:
		Logger();
		bool initialize();
		int writeToLog(std::string message);
		int createLog();
		int deleteLog();
		void shutdown();

	private:
		std::string dataLogName;
		//std::string dataLogLocation;
		bool dataLogExists;
		std::string dataMessage;
		//ofstream dataLog;


};