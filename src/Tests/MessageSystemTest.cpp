#include "gtest/gtest.h"
#include <iostream>
#include "Subject.h"
#include "IObserver.h"

template <typename T>
class Observer1:public Observer<T>
{
public: T theMessage;
		virtual void update(T *message)
		{
	
			 theMessage = *message;

		}
		 std::string who; 

		
	};


template <typename T>
class Observer2:public Observer<T>
{
public: T theMessage;
		virtual void update(T *message)
		{
	
			 theMessage = *message;

		}
		 std::string who; 

		
	};

template <typename T>
class Observer3:public Observer<T>
{
public: T theMessage;
		virtual void update(T *message)
		{
	
			 theMessage = *message;

		}
		 std::string who; 

		
	};


//This test is to make sure observer 1 is attaching correctly.
TEST(messageTest, test_one)
{


	std::string theMessage;
	theMessage ="The shared message";
	Observer1<std::string> observer1;
	Observer2<std::string> observer2;
	Observer3<std::string> observer3;

	observer1.who = "Observer 1 is attached";
	observer2.who = "Observer 2 is attached";
	observer3.who = "Observer 3 is attached";
	Subject<std::string> subject;

	
	subject.attach(observer1);
	
	subject.attach(observer2);
	subject.attach(observer3);



	EXPECT_EQ("Observer 1 is attached", (((Observer1<std::string>*)subject.list.at(0)) ->who));


}

//This test is to make sure observer 2 is attaching correctly.
TEST(messageTest, test_two)
{
	std::string theMessage;
	theMessage ="The shared message";
	Observer1<std::string> observer1;
	Observer2<std::string> observer2;
	Observer3<std::string> observer3;

	observer1.who = "Observer 1 is attached";
	observer2.who = "Observer 2 is attached";
	observer3.who = "Observer 3 is attached";
	Subject<std::string> subject;

	subject.attach(observer1);
	
	subject.attach(observer2);
	subject.attach(observer3);


	EXPECT_EQ("Observer 2 is attached", (((Observer1<std::string>*)subject.list.at(1)) ->who));
	
}

//This test is to make sure observer 3 is attaching correctly.
TEST(messageTest, test_three)
{
	std::string theMessage;
	theMessage ="The shared message";
	Observer1<std::string> observer1;
	Observer2<std::string> observer2;
	Observer3<std::string> observer3;

	observer1.who = "Observer 1 is attached";
	observer2.who = "Observer 2 is attached";
	observer3.who = "Observer 3 is attached";
	Subject<std::string> subject;

	subject.attach(observer1);
	
	subject.attach(observer2);
	subject.attach(observer3);


	EXPECT_EQ("Observer 3 is attached", (((Observer1<std::string>*)subject.list.at(2)) ->who));
	
}

//This test is to make sure observer 1 is being unattached succsesfully.
TEST(messageTest, test_four)
{
	std::string theMessage;
	theMessage ="The shared message";
	Observer1<std::string> observer1;
	Observer2<std::string> observer2;
	Observer3<std::string> observer3;

	observer1.who = "Observer 1 is attached";
	observer2.who = "Observer 2 is attached";
	observer3.who = "Observer 3 is attached";
	Subject<std::string> subject;

	subject.attach(observer1);
	
	subject.attach(observer2);
	subject.attach(observer3);
	subject.unattach(observer1);


	EXPECT_EQ("Observer 2 is attached", (((Observer1<std::string>*)subject.list.at(0)) ->who));
	
}

//This test is to make sure each observer is getting the message. And storing the message correctly.
TEST(messageTest, test_five)
{
	std::string theMessage;
	theMessage ="The shared message";
	Observer1<std::string> observer1;
	Observer2<std::string> observer2;
	Observer3<std::string> observer3;

	observer1.who = "Observer 1 is attached";
	observer2.who = "Observer 2 is attached";
	observer3.who = "Observer 3 is attached";
	Subject<std::string> subject;

	subject.attach(observer1);
	
	subject.attach(observer2);
	subject.attach(observer3);
	subject.notifyObservers(theMessage);


	EXPECT_EQ("The shared message", (((Observer1<std::string>*)subject.list.at(0)) ->theMessage));
	EXPECT_EQ("The shared message", (((Observer1<std::string>*)subject.list.at(1)) ->theMessage));
	EXPECT_EQ("The shared message", (((Observer1<std::string>*)subject.list.at(2)) ->theMessage));
	
}

//This test is to make sure each observer is getting the message. And storing the message correctly.
//But this time the test is with ints. Using the same 3 observers that were used in previous test with strings.
TEST(messageTest, test_six)
{
	int theMessage;
	theMessage = 5;

	Observer1<int> observer1;
	Observer2<int> observer2;
	Observer3<int> observer3;

	Subject<int> subject;

	subject.attach(observer1);
	
	subject.attach(observer2);
	subject.attach(observer3);
	subject.notifyObservers(theMessage);



	EXPECT_EQ(5, (((Observer1<int>*)subject.list.at(0)) ->theMessage));
	EXPECT_EQ(5, (((Observer1<int>*)subject.list.at(1)) ->theMessage));
	
}



//This test combines all functions. We test to make sure the observers that are attached
//are getting the new messages. Multible messages are sent this time. We are also making
//Sure that observers that have been unattached are not reciving the new messages.
TEST(messageTest, test_seven)
{
	std::string theMessage;
	theMessage ="The shared message";
	Observer1<std::string> observer1;
	Observer2<std::string> observer2;
	Observer3<std::string> observer3;

	observer1.who = "Observer 1 is attached";
	observer2.who = "Observer 2 is attached";
	observer3.who = "Observer 3 is attached";
	Subject<std::string> subject;

	subject.attach(observer1);
	
	subject.attach(observer2);
	subject.attach(observer3);
	subject.notifyObservers(theMessage);


	EXPECT_EQ("The shared message", (((Observer1<std::string>*)subject.list.at(0)) ->theMessage));
	EXPECT_EQ("The shared message", (((Observer1<std::string>*)subject.list.at(1)) ->theMessage));
	EXPECT_EQ("The shared message", (((Observer1<std::string>*)subject.list.at(2)) ->theMessage));
	
	theMessage ="The new message";
	subject.unattach(observer2);
	subject.notifyObservers(theMessage);

	EXPECT_EQ("The new message", (((Observer1<std::string>*)subject.list.at(0)) ->theMessage));
	EXPECT_EQ("The new message", (((Observer1<std::string>*)subject.list.at(1)) ->theMessage));
	EXPECT_EQ("The shared message", observer2.theMessage);
	
}

