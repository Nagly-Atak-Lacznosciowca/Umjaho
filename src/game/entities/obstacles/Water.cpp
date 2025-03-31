#include "game/entities/obstacles/Water.h"
#include <cstdlib>

Water::Water(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture* texture) : Obstacle(x, y, width, height, angle, zIndex, texture) {
    isCollidable = false;
}

void Water::activeAction(Car* car) {
    if (SDL_GetTicks() - car->lastWaterTime > 1000) {
        double random = 0.01 + (std::rand() / (RAND_MAX / (0.025 - 0.01)));
        if (rand() % 2 == 0) {
            car->turnAngle = random;
        }
        else {
            car->turnAngle = -random;
        }
        car->lastOilTime = SDL_GetTicks();
    }
}