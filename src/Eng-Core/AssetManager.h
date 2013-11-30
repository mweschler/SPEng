#include <string>
#include <fstream>
#include <map>
#pragma once
#include "Asset.h"
#include "Logger.h"
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
		
     	template <class T> Asset* loadAsset(string assetName)
		{
			Logger &log = *Logger::Instance();
			Derived_from<T, Asset>();
			T* asset = new T(assetName);
			if(checkForDuplicate(assetName))
			{
				
				assetStorage.at(assetName)->increaseRefCount();
				return asset;
			}
			else
			{
			asset->load();
			assetStorage.insert(pair<string,Asset*>(asset->getName(), asset));
				
			log.writeToLog("Asset \"" + assetName + "\" has been loaded to memory.");
				return asset;
			}				
		}
		
		bool releaseAsset(string name);
		

	private:
		string currentAssetName;
		string currentAssetLocation;
		map<string, Asset*> assetStorage;

		
		static AssetManager* instance;
		AssetManager();
		AssetManager(AssetManager const&);
		AssetManager& operator=(AssetManager const&);
		



};