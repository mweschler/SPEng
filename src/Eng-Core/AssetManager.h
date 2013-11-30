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
		
     	template <class T> Asset* loadAsset(string assetName)
		{
			Derived_from<T, Asset>();
			T* asset = new T();
			asset->assetSetName(assetName);
			if(checkForDuplicate(assetName))
			{
				
				assetStorage.at(assetName)->increaseRefCount();
				return asset;
			}
			else
			{
			asset->load(assetName);
			assetStorage.insert(pair<string,Asset*>(asset->getName(), asset));
				cout << "inside asset catch\n";
				
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