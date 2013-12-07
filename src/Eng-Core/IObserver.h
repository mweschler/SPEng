#pragma once


template <typename T>
class Observer
{
public:
	/*! this method is passed a message that the user can do anything they want with.
		\param type what you want to do with the message in the method  */
	virtual void update(T *message) {};


};