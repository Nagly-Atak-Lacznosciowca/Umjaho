#include "engine/sounds/SoundPlayback.h"
#include "SDL3/SDL_log.h"

const unsigned int SoundPlayback::MAX_PLAYBACK_VOLUME = 127;

SoundPlayback::SoundPlayback(SDL_AudioStream *stream, Uint8 *data, int length, SoundPlaybackOptions options): stream(stream), data(data), length(length)  {
	// SDL_AudioSpec spec;
	//
	// if (!SDL_GetAudioStreamFormat(stream, &spec, nullptr)) {
	// 	SDL_Log("Couldn't get audio stream format: %s", SDL_GetError());
	// }
	//
	// Uint8 *temp = (Uint8*)SDL_malloc(this->length * sizeof(Uint8));
	//
	// if (!SDL_MixAudio(temp, this->data, spec.format, this->length, (float)options.volume / SoundPlayback::MAX_PLAYBACK_VOLUME)) {
	// 	SDL_Log("Couldn't mix audio: %s", SDL_GetError());
	// }
	//
	// SDL_memcpy(this->data, temp, this->length);
	
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