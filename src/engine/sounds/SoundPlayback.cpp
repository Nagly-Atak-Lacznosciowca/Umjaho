#include "engine/sounds/SoundPlayback.h"

SoundPlayback::SoundPlayback(SDL_AudioStream *stream, Uint8 *data, int length): stream(stream), data(data), length(length)  {}