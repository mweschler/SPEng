#pragma once
#include <string>
#include <fstream>


//h file for logger class
class Asset{

	public:
		std::string getName();
		bool virtual load(std::string fileName);
		void assetSetName(std::string name);
		Asset();
		//Asset(std::string name);
	    void decreaseRefCount();
	   	void increaseRefCount();
	    bool releaseAsset();
		int getRefCount();

		
		
	private:
		int dataRefCount;
		std::string dataName;
		
};