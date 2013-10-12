#pragma once

class IGameplayFoundation {
public:
	virtual void update(int) = 0;
	template <typename T>
	virtual T getAttribute(std::string) = 0;
	template <typename S>
	virtual S setAttribute(std::string) = 0;
};