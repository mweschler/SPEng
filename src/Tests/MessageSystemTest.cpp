#include "gtest/gtest.h"
#include <iostream>
#include "Subject.h"
#include "IObserver.h"

template <typename T>
class Observer1:public Observer<T>
{
		std::string theMessage;
		virtual void update(T *message)
		{

			 theMessage = *message;

		}
	};

template <typename T>
class Observer2:public Observer<T>
{
		std::string theMessage;
		virtual void update(T *message)
		{

			 theMessage = *message;

		}
	};



template <typename T>
class Observer3:public Observer<T>
{
		std::string theMessage;
		virtual void update(T *message)
		{

			 theMessage = *message;

		}
	};

TEST(messageTest, test_one)
{
	std::string theMessage;
	Observer1<std::string> observer1;
	Observer2<std::string> observer2;
	Observer3<std::string> observer3;


	Subject<std::string> subject;
	subject.attach(&(Observer<std::string>)observer1);
	subject.attach(&(Observer<std::string>)observer2);
	subject.attach(&(Observer<std::string>)observer3);
	



}