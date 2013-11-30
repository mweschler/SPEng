#include <string>
#include <fstream>
#include <iostream>
#include "Logger.h"
#include "Asset.h"
using namespace std;

		string dataName;
		int dataRefCount = 1;


		/*Asset::Asset(string nameOfAsset)
		{
			  dataName = nameOfAsset;
			  dataRefCount = 1;
		}*/

		Asset::Asset()
		{
		}

		void Asset::assetSetName(std::string name)
		{
			dataName = name;
			//dataRefCount = 1;
		}
	    
		string Asset::getName()
		{
			return dataName;
		}

		
		void Asset::decreaseRefCount()
		{
			dataRefCount--;
		}

		void Asset::increaseRefCount()
		{
			dataRefCount++;
		}

		bool Asset::releaseAsset()
		{
			cout << "Release asset\n";
			return true;
		}

		int Asset::getRefCount()
		{
			return dataRefCount;
		}

		
		bool Asset::load(string fileName)
		{

			Logger &log = *Logger::Instance();
			log.writeToLog("load being used");

			return true;
		}