#include <vector>
class Subject
{

public:
	std::vector<std::string> observerList;

	virtual void attach();
	virtual void unattach();
	virtual void notifyObservers();

};