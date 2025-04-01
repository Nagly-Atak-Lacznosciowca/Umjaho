#ifndef RAY_H
#define RAY_H

#include <cmath>

#include "SDL3/SDL_rect.h"

struct Ray {
    SDL_FPoint origin;
    SDL_FPoint direction;
    mutable bool collides = false;

};

#endif //RAY_H
