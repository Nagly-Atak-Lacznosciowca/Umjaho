#ifndef UMJAHO_PLAYER_H
#define UMJAHO_PLAYER_H

#include "engine/Renderer.h"
#include "game/entity/Car.h"

class Player : public Car {
    public:
        Player(double x, double y, double z, SDL_Texture* texture);
};

#endif //UMJAHO_PLAYER_H
