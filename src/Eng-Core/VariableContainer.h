#pragma once
#include <String>

template <typename T>
class VariableContainer
{
private:
	std::string name;
	T type;
	std::string value;
public:
	std::string retrieveName(std::string);
	T retrieveType(std::string);
	std::string retrieveValue(std::string);

	void modifyName(std::string, std::string);
	void modifyType(std::string, T);
	void modifyValue(std::string, std::string);
};