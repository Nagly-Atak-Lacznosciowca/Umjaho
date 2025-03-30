#ifndef BARREL_H
#define BARREL_H

#include "game/entities/Car.h"
#include "game/entities/obstacles/Obstacle.h"

class Cone : public Obstacle {
    public:
        Cone(double x, double y, double width = 25, double height = 25, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
        ~Cone() override = default;

        void activeAction(Car* car) override;
};

#endif //BARREL_H
