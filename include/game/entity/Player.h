#ifndef UMJAHO_PLAYER_H
#define UMJAHO_PLAYER_H

#include "engine/Renderer.h"
#include "game/entity/Car.h"

class Player : public Car {
    public:
        Player(double x, double y, double width = Car::WIDTH, double length = Car::LENGTH, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
        int nitroTimer = 0;
        bool nitroActive = false;
        int nitroCharges = 0;
};

#endif //UMJAHO_PLAYER_H
