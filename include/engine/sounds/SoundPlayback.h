#ifndef UMJAHO_SOUNDPLAYBACK_H
#define UMJAHO_SOUNDPLAYBACK_H

#include "SDL3/SDL_audio.h"

union SoundPlaybackOptions {
	struct {
		bool looping: 1;
	};
	unsigned int Uint8;
};

class SoundPlayback {
	public:
		SDL_AudioStream *stream;
		Uint8 *data;
		int length;
		
		SoundPlayback(SDL_AudioStream *stream, Uint8 *data, int length, SoundPlaybackOptions options = {});
		~SoundPlayback();
		
		bool play();
		bool stop();
};

#endif //UMJAHO_SOUNDPLAYBACK_H
