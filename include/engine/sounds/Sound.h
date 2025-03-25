#ifndef UMJAHO_SOUND_H
#define UMJAHO_SOUND_H

#include "SDL3/SDL_audio.h"

class Sound {
	public:
		SDL_AudioStream *stream;
		Uint8 *data;
		int length;
		
		Sound();
		~Sound();
};

#endif //UMJAHO_SOUND_H
