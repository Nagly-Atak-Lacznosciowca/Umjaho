#include <stdexcept>

#include "SDL3/SDL_log.h"

#include "engine/sounds/SoundManager.h"
#include "game/Game.h"

SoundManager::SoundManager(): sounds({}), id(0) {}

void SoundManager::registerSound(const std::string &name, Sound *sound)
{
	this->sounds.insert({name, sound});
}

SoundPlayback* SoundManager::playSound(Sound *sound)
{
	const auto stream = SDL_CreateAudioStream(sound->spec, nullptr);
	
	if (stream == nullptr)
		SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
	
	if (!SDL_BindAudioStream(Game::audioDeviceID, stream))
		SDL_Log("Couldn't bind audio: %s", SDL_GetError());
	
	const auto playback = new SoundPlayback(stream, sound->data, sound->length, {
		.looping = true
	});
	
	playback->play();
	
	return playback;
}

SoundPlayback* SoundManager::playSound(const std::string &name)
{
	auto sound = this->sounds.at(name);
	
	return this->playSound(sound);
}

bool SoundManager::setVolume(float volume)
{
	return SDL_SetAudioDeviceGain(Game::audioDeviceID, volume);
}

float SoundManager::getVolume() {
	return SDL_GetAudioDeviceGain(Game::audioDeviceID);
}