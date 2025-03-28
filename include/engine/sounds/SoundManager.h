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
		
		SoundManager();
		~SoundManager() = default;
		
		void registerSound(const std::string &name, Sound* sound);
		SoundPlayback* playSound(Sound* sound);
		SoundPlayback* playSound(const std::string &name);
	
	private:
		int id;
};

#endif //UMJAHO_SOUNDMANAGER_H
