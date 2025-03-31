#ifndef SPEEDBUMP_H
#define SPEEDBUMP_H

#include "game/entities/obstacles/Obstacle.h"

class SpeedBump : public Obstacle {
    public:
        SpeedBump(double x, double y, double width = 100, double height = 20, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);

        void activeAction(Car* car) override;
};

#endif //SPEEDBUMP_H
