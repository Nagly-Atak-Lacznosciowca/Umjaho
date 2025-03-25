#ifndef UMJAHO_SOUNDMANAGER_H
#define UMJAHO_SOUNDMANAGER_H

#include <string>
#include <map>
#include <queue>

#include "engine/sounds/Sound.h"
#include "engine/sounds/SoundPlayback.h"

class SoundManager {
	public:
		std::map<std::string, Sound*> sounds;
		std::queue<SoundPlayback*> playing;
		
		SoundManager();
		~SoundManager();
		
		void registerSound(std::string name, Sound* sound);
		int playSound(Sound* sound);
		int playSound(std::string name);
		bool stopSound(int id);
	
	private:
		int id = 0;
};

#endif //UMJAHO_SOUNDMANAGER_H
