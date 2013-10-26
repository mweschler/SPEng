#include "Subject.h"
#include <vector>
#include <list>
#include "IObserver.h"
/**
template <typename T>
void Subject<T>::attach(Observer<T> *concreteObserver)
{
	list.push_back(concreteObserver);
}

template <typename T> 
void Subject<T>::unattach(Observer<T>  *concreteObserver)
{
	//This might not be correct
	list.erase(std::remove(list.begin(), list.end(), concreteObserver), end());

}

//This might not need to be generic.
//Still figureing out what message is. Mabey a string?
template <typename T> 
void Subject<T>::notifyObservers(T message)
{
	/**
		//iterate through list of observers  and update info. 
    for(vector<concreteObserver*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->update(message);
        }
    }

	**/
	//iterate through list of observers  and update info. 
 //   for(vector<concreteObserver*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
 //   {
  //      if(*iter != 0)
   //     {
  //          (*iter)->update(message);
   //     }
  //  }
//}
/**

A class that is implementing my code would look something like this
Class is AudioManager
#include Subject.h

class AudioManager : Subject
{
notify(message);

}

This would send message to all attached observers

**/