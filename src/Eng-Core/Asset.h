#pragma once
#include <string>
#include <fstream>


//h file for logger class
class Asset{

	public:
		/*!
		\return returns the name of the Asset.
		*/
		std::string getName();

		/*!
		\param the name of the file that user wishes to load
		\return returns true upon successful laoding of asset
		*/
		bool virtual load(std::string fileName);

		/*!
		\param the name of the file the Asset will be assigned to.
		*/
		void assetSetName(std::string name);

		

		
		Asset();
		//Asset(std::string name);
	    /*! decreases the reference count of an asset by 1*/
		void decreaseRefCount();

		/*! increases the reference count of an asset by 1*/
	   	void increaseRefCount();

		/*! resets the reference count of the asset to 1*/
		void startRefCount();

		/*! releases an asset from memory, ensuring no other game component requires the asset
		\return returns true upon successful asset release
		*/
	    bool releaseAsset();

		/*! Retrieves the amount of references made to the asset by other game components.
		\return the reference count of the asset.
		*/
		int getRefCount();

		
		
	private:
		int dataRefCount;
		std::string dataName;
		
};