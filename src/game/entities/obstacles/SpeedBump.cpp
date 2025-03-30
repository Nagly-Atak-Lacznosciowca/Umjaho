#include "game/entities/obstacles/SpeedBump.h"

SpeedBump::SpeedBump(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture* texture) : Obstacle(x, y, width, height, angle, zIndex, texture) {
    isCollidable = false;
}

void SpeedBump::activeAction(Car* car) {
    if (car->speed > Car::MAX_SPEED/2) {
        car->speed = Car::MAX_SPEED/2;
    }
}