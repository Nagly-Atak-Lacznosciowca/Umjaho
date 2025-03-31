#include "game/entities/surfaces/Ice.h"
#include "game/Game.h"

Ice::Ice(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture* texture) : Surface(x, y, width, height, angle, zIndex, texture) {}

void Ice::action(Car* car) {
    car->enterIce();
}