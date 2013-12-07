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
		/*!retrieves the singleton AssetManager of the system.
		/return a pointer to the system's AssetManager
		*/
		static AssetManager* Instance();

		/*! Checks to see if the asset the user wants to load is already loaded onto memory
		/param the name of the asset to check if it exists already
		/return true if there is an asset with the parameter's same name exists
		*/
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

		/*! Retrieves reference count of asset
		/param name of asset for which you'd like to retrieve the reference count from.
		/return number of references other game components use on requested asset.
		*/
		int getRefCount(string name);
		 
		/*! Creates an asset and stores it onto game memory. 
		/param name of file to save as an asset onto game engine.
		/return the created asset derived from the user's file request.
		*/
     	template <class T> Asset* loadAsset(string assetName)
		{
			Logger &log = *Logger::Instance();
			Derived_from<T, Asset>();
			T* asset = new T();
			asset->assetSetName(assetName);
			if(checkForDuplicate(assetName))
			{			
				assetStorage.at(assetName)->increaseRefCount();
				return assetStorage.at(assetName);
			}
			else
			{

			if(!asset->load(assetName)){
				log.writeToLog("Asset \"" + assetName + "\" could not be loaded to memory.");
				return NULL;
			}

			assetStorage.insert(pair<string,Asset*>(asset->getName(), asset));
			asset->startRefCount();
				
			log.writeToLog("Asset \"" + assetName + "\" has been loaded to memory.");

				return asset;
			}				
		}
		
		/*! releases an asset from game memory
		/param name of asset to be released from memory
		/return returns true upon sucecssful release of asset
		*/
		bool releaseAsset(string name);
		

	private:
		
		/*! data structure used to keep track of all the game assets */
		map<string, Asset*> assetStorage;

		
		static AssetManager* instance;
		AssetManager();
		AssetManager(AssetManager const&);
		AssetManager& operator=(AssetManager const&);
		



};