#include <stdexcept>

#include "engine/sounds/SoundManager.h"

SoundManager::SoundManager(): sounds({}), playing(1024), id(0) {}

void SoundManager::registerSound(std::string name, Sound *sound)
{
	this->sounds.insert({name, sound});
}

int SoundManager::playSound(Sound *sound)
{
	this->playing.push_back(new SoundPlayback(/*some data*/));
	
	return 0;
}

int SoundManager::playSound(std::string name)
{
	auto sound = this->sounds.at(name);
	
	this->playSound(sound);
	
	return 0;
}

bool SoundManager::stopSound(int id)
{
	throw std::runtime_error("Not implemented error");
}