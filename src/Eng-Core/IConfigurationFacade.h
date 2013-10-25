#pragma once
#include <String>

template <typename V>
class IConfigurationFacade
{
public:
	virtual V retrieveVariable(std::string) = 0;
	virtual bool storeVariable(std::string) = 0;
	virtual bool modifyVariable(std::string, std::string ) = 0;
};