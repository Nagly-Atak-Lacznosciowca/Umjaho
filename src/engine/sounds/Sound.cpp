#include "engine/sounds/Sound.h"

Sound::Sound(SDL_AudioStream *stream, Uint8 *data, int length): stream(stream), data(data), length(length) {}