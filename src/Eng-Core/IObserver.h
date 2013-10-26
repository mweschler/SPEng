#pragma once

template <typename T>
class IObservers
{
public:
 virtual void notify(T message);
 //virtual void storeMessage();

};