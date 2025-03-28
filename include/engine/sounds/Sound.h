#ifndef UMJAHO_SOUND_H
#define UMJAHO_SOUND_H

#include "SDL3/SDL_audio.h"

class Sound {
	public:
		SDL_AudioSpec *spec;
		Uint8 *data;
		int length;
		
		Sound(SDL_AudioSpec *spec, Uint8 *data, int length);
		~Sound() = default;
};

#endif //UMJAHO_SOUND_H
