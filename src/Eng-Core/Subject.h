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


	virtual void attach(Observer<T> &concreteSubject)
	{
		//std::cout << " in attach /n";
	list.push_back(&concreteSubject);
	//list.insert(&concreteSubject);
	
    }


	
	virtual void unattach(Observer<T> *concreteSubject)

	{
		//std::string thing;

		list.erase(std::remove(list.begin(), list.end(), concreteSubject), list.end());

		 /**
		 for(it = list.begin() ; it !=list.end() ; it++) 
		 {
			 if(it.data == concreteSubject )
			 {
				 list.erase(it);
				 return;



			 }


		 }
	

	**/

	}
	//Not yet sure if i want message to be string
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