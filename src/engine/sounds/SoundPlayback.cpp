#include "engine/sounds/SoundPlayback.h"
#include "SDL3/SDL_log.h"

SoundPlayback::SoundPlayback(SDL_AudioStream *stream, Uint8 *data, int length, SoundPlaybackOptions options): stream(stream), data(data), length(length)  {
	if (options.looping)
	{
		SDL_SetAudioStreamGetCallback(this->stream, [](void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount) -> void {
			if (additional_amount == total_amount)
				((SoundPlayback*)userdata)->play();
		}, this);
	}
}

SoundPlayback::~SoundPlayback() {
	SDL_DestroyAudioStream(stream);
}

bool SoundPlayback::play() {
	return SDL_PutAudioStreamData(this->stream, this->data, this->length);
}

bool SoundPlayback::stop() {
	return SDL_SetAudioStreamGetCallback(this->stream, nullptr, nullptr) && SDL_ClearAudioStream(this->stream);
}