#include "engine/sounds/SoundPlayback.h"

SoundPlayback::SoundPlayback(SDL_AudioStream *stream, Uint8 *data, int length, SoundPlaybackOptions options): stream(stream), data(data), length(length)  {
	if (options.looping)
	{
		SDL_SetAudioStreamGetCallback(this->stream, [](void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount) -> void {
			((SoundPlayback*)userdata)->play();
		}, this);
	}
}

bool SoundPlayback::play() {
	return SDL_PutAudioStreamData(this->stream, this->data, this->length);
}

bool SoundPlayback::pause() {
	return SDL_PauseAudioStreamDevice(this->stream);
}

bool SoundPlayback::resume() {
	return SDL_ResumeAudioStreamDevice(this->stream);
}