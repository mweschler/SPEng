#pragma once
#include <string>
#include <fstream>


//h file for logger class
class Asset{


	public:
		std::string getName();
		bool virtual load(std::string name);
		Asset();
		Asset(std::string name);
	    void decreaseRefCount();
	   	void increaseRefCount();
	    bool release(Asset asset);
		int getRefCount();
		void createAsset();
		

	private:
		int dataRefCount;
		std::string dataName;
		std::string dataLocation;
		std::string dataType;	

};