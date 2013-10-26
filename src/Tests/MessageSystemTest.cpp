#include "gtest/gtest.h"
#include <iostream>
#include "Subject.h"
#include "IObserver.h"

template <typename T>
class Observer1:public Observer<T>
{
public: std::string theMessage;
		virtual void update(T *message)
		{
		//	std::cout << "yolo Swag /n";
			 theMessage = *message;

		}
		 std::string who; 
	//	 void hey()
	//	 {
			
//			std::cout << "MIKE IS SWINDLER      sss  ";
//		 }
		
	};

template <typename T>
class Observer2:public Observer<T>
{
		std::string theMessage;
		virtual void update(T *message)
		{

			 theMessage = *message;

		}
	//	std::string who ="Im Observer 2 /n";
	};



template <typename T>
class Observer3:public Observer<T>
{
		std::string theMessage;
		virtual void update(T *message)
		{

			 theMessage = *message;

		}
//		std::string who ="Im Observer 3 /n";
	};

TEST(messageTest, test_one)
{
	std::string theMessage;
	theMessage ="Yolo Swag";
	Observer1<std::string> observer1;
	Observer2<std::string> observer2;
	Observer3<std::string> observer3;

	observer1.who = "WE IS TESTING STUFF/n";
	Subject<std::string> subject;

	/* MIKE NOTE:
	OLD: subject.attach(((Observer<std::string>)observer1));
	This cast was the problem. Didn't need to cast it.
	Parameter of attach is a reference(Observer &observer) so you
	can safely give a child of observer and it will be cast as a reference
	automaticly

	subject.attach((Observer<std::string>&)observer1);
	or
	subject.attach(dynamic_cast<Observer<std::string>&>(observer1));
	would be a correct cast in this case, but not really necessary
	*/
	
	subject.attach(observer1);
	
	//subject.attach(&(Observer<std::string>)observer2);
//	subject.attach(&(Observer<std::string>)observer3);

	/* MIKE NOTE:
	This line was fine. You could use dynamic_cast to do a checked cast as well
	std::cout << dynamic_cast<Observer1<std::string>*>(subject.list.at(0))->who;
	*/
	std::cout <<(((Observer1<std::string>*)subject.list.at(0)) ->who);

//	std::cout << subject.list.at(1);
	//std::cout << subject.list.at(2);
	//subject.notifyObservers(theMessage);


//	EXPECT_EQ("yolo Swag", observer1.theMessage);



}