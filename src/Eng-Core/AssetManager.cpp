#include "AssetManager.h"
#include "Asset.h"
#include <sys/stat.h>
#include <iostream>

using namespace std;

AssetManager* AssetManager::instance = NULL;

		string currentAssetName;
		string currentAssetLocation;
		map<string, Asset*> assetStorage;
	

		AssetManager::AssetManager()
		{

		}

		AssetManager* AssetManager::Instance()
		{
			cout << "inside instance\n";
			if(instance == NULL)
			{
				cout << "inside instance is NULL\n";
				instance = new AssetManager();
			}
			return instance;
		}
		

		
		bool AssetManager::releaseAsset(string assetName)
		{
			if(checkForDuplicate(assetName))
			{
				if(assetStorage.at(assetName)->getRefCount() > 1)
				{
					assetStorage.at(assetName)->decreaseRefCount();
				}
				else
				{
					assetStorage.erase(assetName);
				}
				return true;
			}
			else
			{
				cout << "failed to release asset. Asset never loaded.";
				return false;
			}
			
		}
		

	    
		//string currentAssetName;
		
		/*
		string currentAssetLocation;
		map<string, Asset> assetStorage;
		*/
		bool AssetManager::checkForDuplicate(string name)
		{
			try
			{
				Asset* a = assetStorage.at(name);
				return true;
			}
			catch(const exception& e)
			{
				return false;
			}
		}
		/*
		int createAsset(Asset asset);
		int addAsset(string name);
	    int increaseRefcount(string name);
		int decreaseRefCount(string name);
		*/

		int AssetManager::getRefCount(string name)
		{
			return assetStorage.at(name) -> getRefCount();		
		}
		/*
		static AssetManager* instance;
		AssetManager();
		AssetManager(AssetManager const&);
		AssetManager& operator=(AssetManager const&);
		*/