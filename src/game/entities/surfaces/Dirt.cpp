#include "game/entities/surfaces/Dirt.h"
#include "game/Game.h"

Dirt::Dirt(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture* texture) : Surface(x, y, width, height, angle, zIndex, texture) {}

void Dirt::action(Car* car) {
    car->enterDirt();
}