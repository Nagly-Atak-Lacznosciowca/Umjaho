#ifndef UMJAHO_SOUNDMANAGER_H
#define UMJAHO_SOUNDMANAGER_H

#include <string>
#include <map>

#include "SDL3/SDL_audio.h"

#include "engine/sounds/Sound.h"
#include "engine/sounds/SoundPlayback.h"
#include "datatypes/CircularBuffer.h"

class SoundManager {
	public:
		std::map<std::string, Sound*> sounds;
		CircularBuffer<SoundPlayback*> playing = CircularBuffer<SoundPlayback *>(1024);
		
		SoundManager();
		~SoundManager() = default;
		
		void registerSound(std::string name, Sound* sound);
		int playSound(Sound* sound);
		int playSound(std::string name);
		bool stopSound(int id);
	
	private:
		int id;
};

#endif //UMJAHO_SOUNDMANAGER_H
