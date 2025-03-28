#ifndef UMJAHO_SOUNDPLAYBACK_H
#define UMJAHO_SOUNDPLAYBACK_H

#include "SDL3/SDL_audio.h"

class SoundPlayback {
	public:
		SDL_AudioStream *stream;
		Uint8 *data;
		int length;
		
		SoundPlayback(SDL_AudioStream *stream, Uint8 *data, int length);
		~SoundPlayback() = default;
};

#endif //UMJAHO_SOUNDPLAYBACK_H
