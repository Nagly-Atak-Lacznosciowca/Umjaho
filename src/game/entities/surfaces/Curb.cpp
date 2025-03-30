#include "game/entities/surfaces/Curb.h"
#include "game/Game.h"

Curb::Curb(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture* texture) : Surface(x, y, width, height, angle, zIndex, texture) {}

void Curb::action(Car* car) {
    car->enterCurb();
}