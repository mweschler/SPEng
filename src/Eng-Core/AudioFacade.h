#pragma once
#include <String>

class IAudioFacade
{
public:
	virtual bool fadeAudio(std::string) = 0;
	virtual bool playAudio(std::string) = 0;
	virtual bool loopAudio(std::string) = 0;
};