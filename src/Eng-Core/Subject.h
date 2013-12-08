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
	/*! A vector that contains a list of observers*/
	 std::vector<Observer<T> * > list;

	 /*! Pushes an observer onto the observer list
		\param type the address of an obsever you wish to attach*/
	virtual void attach(Observer<T> &concreteSubject)
	{
		
	list.push_back(&concreteSubject);
	
	
    }


	/*! Remove and observer from the observer list
		\param type the address of an obsever you wish to unattach */
	virtual void unattach(Observer<T> &concreteSubject)

	{
		
		list.erase(std::remove(list.begin(), list.end(), &concreteSubject), list.end());


	}
	/*! call the update method of all observers passing what ever kind of message you wish
		\param type the message you want to pass to all observers */
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