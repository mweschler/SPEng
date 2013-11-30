#include <string>
#include <fstream>
#include <iostream>
#include "Asset.h"
using namespace std;

		string dataName;
		int dataRefCount;


		Asset::Asset(string nameOfAsset)
		{
			  dataName = nameOfAsset;
			  dataRefCount = 1;
		}

		Asset::Asset()
		{
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

		
		bool Asset::load()
		{
			cout << "Load file\n";
			return true;
		}