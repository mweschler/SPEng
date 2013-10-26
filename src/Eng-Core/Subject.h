#pragma once
#include <string>
#include <vector>
#include <list>

//	

template <typename T>
class Subject
{

public:
	//Vector filled with pointers to the observers
	std::vector<T* > list;

	virtual void attach(T *concreteSubject);
	virtual void unattach(T *concreteSubjecct);
	//Not yet sure if i want message to be string
	virtual void notifyObservers(T message);

};