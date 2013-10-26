#include "VariableContainer.h"
#include <string>


template <typename T>
std::string VariableContainer<T>::retrieveName(std::string){
	return name;
}

template <typename T>
T VariableContainer<T>::retrieveType(std::string){
	return type;
}

template <typename T>
std::string VariableContainer<T>::retrieveValue(std::string){
	return value;
}

template <typename T>
void VariableContainer<T>::modifyName(std::string, std::string){
	
}

template <typename T>
void VariableContainer<T>::modifyType(std::string, T){

}

template <typename T>
void VariableContainer<T>::modifyValue(std::string, std::string){

}