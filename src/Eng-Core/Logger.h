#include <string>
#include <fstream>
using namespace std;


//h file for logger class
class Logger{
	public:
		static Logger* Instance();	
		bool initialize();
		int writeToLog(std::string message);
		int createLog();
		int deleteLog();
		void shutdown();
		string getDataLogName();
		bool getDataLogExists();

	private:
		//std::string dataLogLocation;
		string dataLogName;
		bool dataLogExists;
		string dataMessage;
		ofstream dataLog;

		static Logger* instance;
		Logger();
		Logger(Logger const&);
		Logger& operator=(Logger const&);



};