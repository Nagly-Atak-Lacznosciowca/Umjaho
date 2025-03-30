#ifndef OIL_H
#define OIL_H

#include "game/entities/obstacles/Obstacle.h"

class Oil : public Obstacle {
    public:
        Oil(double x, double y, double width = 25, double height = 25, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);

        void activeAction(Car* car) override;
};

#endif //OIL_H
