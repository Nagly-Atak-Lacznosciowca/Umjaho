#ifndef UMJAHO_OPPONENT_H
#define UMJAHO_OPPONENT_H

#include "engine/Renderer.h"
#include "game/entity/Car.h"

class Opponent : public Car {
    public:
        Opponent(double x, double y, double z, SDL_Texture* texture);
};

#endif //UMJAHO_OPPONENT_H
