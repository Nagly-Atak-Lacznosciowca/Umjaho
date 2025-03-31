#ifndef UMJAHO_SOUNDPLAYBACK_H
#define UMJAHO_SOUNDPLAYBACK_H

#include "SDL3/SDL_audio.h"

union SoundPlaybackOptions {
	struct {
		bool looping: 1;
		unsigned int volume: 7; // when changing bit amount change SoundPlayback::MAX_PLAYBACK_VOLUM to max uint bit amount eg. 2^7 - 1
	};
	unsigned int Uint8;
};

class SoundPlayback {
	public:
		SDL_AudioStream *stream;
		Uint8 *data;
		int length;
		
		static const unsigned int MAX_PLAYBACK_VOLUME;
		
		SoundPlayback(SDL_AudioStream *stream, Uint8 *data, int length, SoundPlaybackOptions options = {
			.looping = false,
			.volume = SoundPlayback::MAX_PLAYBACK_VOLUME
		});
		~SoundPlayback();
		
		bool play();
		bool stop();
};

#endif //UMJAHO_SOUNDPLAYBACK_H
