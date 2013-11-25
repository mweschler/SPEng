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
		
		

		int AssetManager::getRefCount(string name)
		{
			return assetStorage.at(name) -> getRefCount();		
		}
		
		
		