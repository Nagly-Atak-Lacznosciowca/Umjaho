#ifndef WATER_H
#define WATER_H

#include "game/entities/obstacles/Obstacle.h"

class Water : public Obstacle {
    public:
        Water(double x, double y, double width = 25, double height = 25, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);

        void activeAction(Car* car) override;
};

#endif //WATER_H
