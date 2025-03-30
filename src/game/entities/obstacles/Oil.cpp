#include "game/entities/obstacles/Oil.h"

#include <cstdlib>

Oil::Oil(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture* texture) : Obstacle(x, y, width, height, angle, zIndex, texture) {
    isCollidable = false;
}

void Oil::activeAction(Car* car) {
    if (SDL_GetTicks() - car->lastOilTime > 1000) {
        double random = 0.02 + (std::rand() / (RAND_MAX / (0.05 - 0.02)));
        if (rand() % 2 == 0) {
            car->turnAngle = random;
        }
        else {
            car->turnAngle = -random;
        }
        car->lastOilTime = SDL_GetTicks();
    }
}
