#include <string>
#include <fstream>
#include <map>
#pragma once
#include "Asset.h"
using namespace std;


//h file for logger class
class AssetManager{

	public:
		static AssetManager* Instance();	
		bool checkForDuplicate(string name);
		
		template<class T, class B> struct Derived_from 
		{
			static void constraints(T* p) 
			{ 
				B* pb = p;
			}
			Derived_from() 
			{ 
				void(*p)(T*) = constraints; 
			}
		};

		int getRefCount(string name);
		
     	template <class T> bool loadAsset(string assetName)
		{
			Derived_from<T, Asset>();
			T* asset = new T(assetName);
			if(checkForDuplicate(assetName))
			{
				
				assetStorage.at(assetName)->increaseRefCount();
				return true;
			}
			else
			{
			//asset.load();
			assetStorage.insert(pair<string,Asset*>(asset->getName(), asset));
				cout << "inside asset catch\n";
				
				return true;
			}				
		}
		
		int releaseAsset(string name);
		

	private:
		string currentAssetName;
		string currentAssetLocation;
		map<string, Asset*> assetStorage;

		
		int createAsset(Asset asset);
		int addAsset(string name);
	    int increaseRefcount(string name);
		int decreaseRefCount(string name);
		

		static AssetManager* instance;
		AssetManager();
		AssetManager(AssetManager const&);
		AssetManager& operator=(AssetManager const&);
		



};