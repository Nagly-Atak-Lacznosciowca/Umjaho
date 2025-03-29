#include "game/entities/Opponent.h"
#include "SDL3/SDL.h"

Opponent::Opponent(const double x, const double y, const double width, const double length, const double angle, const double zIndex, SDL_Texture* texture) : Car(x, y, width, length, angle, zIndex, texture) {}