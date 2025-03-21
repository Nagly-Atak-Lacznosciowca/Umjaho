#include "game/entity/Player.h"
#include "SDL3/SDL.h"

Player::Player(double x, double y, double z, SDL_Texture* texture) : Car(x, y, z, texture) {}