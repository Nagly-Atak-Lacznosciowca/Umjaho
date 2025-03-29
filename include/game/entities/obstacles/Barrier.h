#ifndef UMJAHO_BARRIER_H
#define UMJAHO_BARRIER_H
#include "game/entities/obstacles/Obstacle.h"

class Barrier : public Obstacle {
    public:
        Barrier(double x, double y, double width = 100, double height = 40, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
};

#endif //UMJAHO_BARRIER_H
