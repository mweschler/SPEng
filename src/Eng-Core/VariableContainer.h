#pragma once
#include <String>

class VariableContainer
{
public:
	virtual ~VariableContainer() {}
    template<typename T> T getValue();
    template<typename T> void setValue(T newValue);
};

template <typename T>
class Variable : public VariableContainer
{
public:
	Variable(T initialValue) :value(initialValue) {} 
	T getValue() {return value;}
	void setValue(T newValue){value = newValue;}
private:
	T value;
};

//Here's the trick: dynamic_cast rather than virtual
template<typename T> T VariableContainer::getValue()
{ 
	return dynamic_cast<Variable<T>&>(*this).getValue(); 
}
template<typename T> void VariableContainer::setValue(T newValue)
{ 
	return dynamic_cast<Variable<T>&>(*this).setValue(newValue); 
}

