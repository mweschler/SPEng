#pragma once
#include <string>
#include <vector>
#include <list>
#include "IObserver.h"
#include <iterator>
#include <iostream>
#include <algorithm>




template <typename T>
class Subject
{
public:
	//Vector filled with pointers to the observers
	 std::vector<Observer<T> * > list;


	 //Attach observer by pushing observer onto vector list
	virtual void attach(Observer<T> &concreteSubject)
	{
		
	list.push_back(&concreteSubject);
	
	
    }


	//Unattach observer by removing it from list.
	virtual void unattach(Observer<T> &concreteSubject)

	{
		

		list.erase(std::remove(list.begin(), list.end(), &concreteSubject), list.end());

	

	}
	
	virtual void notifyObservers(T message)
	{

		for(std::vector<Observer<T>*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
        {
          if(*iter != 0)
          {
            (*iter)->update(&message);
          }
    }
	}
};