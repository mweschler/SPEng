#pragma once

template <typename T>
class IGameplayFoundation {
public:
	virtual void update(int) = 0;
	virtual T getAttribute(std::string) = 0;
	virtual T setAttribute(std::string) = 0;
};