#include "engine/sounds/Sound.h"

Sound::Sound(SDL_AudioSpec *spec, Uint8 *data, int length): spec(spec), data(data), length(length) {}