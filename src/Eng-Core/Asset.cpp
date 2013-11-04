#include <string>
#include <fstream>
#include <iostream>
#include "Asset.h"
using namespace std;

		string dataName;
		string dataLocation;
		string dataType;
		int dataRefCount;


		Asset::Asset(string nameOfAsset)
		{
			  dataName = nameOfAsset;
			  dataRefCount = 1;
		}
		Asset::Asset()
		{
			  dataName = "sauce";
			  dataRefCount = 1;
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

		bool Asset::release(Asset asset)
		{
			cout << "Release it\n";
			return true;
		}

		int Asset::getRefCount()
		{
			return dataRefCount;
		}

		
		bool Asset::load(string filename)
		{
			cout << "Load file\n";
			return true;
		}