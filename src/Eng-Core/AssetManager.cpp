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
			Logger &log = *Logger::Instance();
			if(instance == NULL)
			{
				log.writeToLog("AssetManager has been created");
				instance = new AssetManager();
			}
			return instance;
		}
		

		
		bool AssetManager::releaseAsset(string assetName)
		{
			Logger &log = *Logger::Instance();
			if(checkForDuplicate(assetName))
			{
				if(assetStorage.at(assetName)->getRefCount() > 1)
				{
					assetStorage.at(assetName)->decreaseRefCount();
					log.writeToLog("decreased reference count of " + assetName + ".");
				}
				else
				{
					//assetStorage.at(assetName)->releaseAsset();
					assetStorage.erase(assetName);

					log.writeToLog("Asset - " + assetName + " has been removed from memory");
				}
				return true;
			}
			else
			{
				log.writeToLog("failed to release asset. Asset never loaded.");
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
		
		
		