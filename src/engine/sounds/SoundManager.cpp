#include <stdexcept>

#include "SDL3/SDL_log.h"

#include "engine/sounds/SoundManager.h"
#include "game/Game.h"

SoundManager::SoundManager(): sounds({}), playing(1024), id(0) {}

void SoundManager::registerSound(std::string name, Sound *sound)
{
	this->sounds.insert({name, sound});
}

int SoundManager::playSound(Sound *sound)
{
	const auto stream = SDL_CreateAudioStream(sound->spec, nullptr);
	
	if (stream == nullptr)
		SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
	
	if (!SDL_BindAudioStream(Game::audioDeviceID, stream))
		SDL_Log("Couldn't bind audio: %s", SDL_GetError());
	
	this->playing.push_back(new SoundPlayback(
		stream,
		sound->data,
		sound->length
	));
	
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