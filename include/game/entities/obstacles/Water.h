#ifndef WATER_H
#define WATER_H

#include "game/Game.h"
#include "game/entities/obstacles/Obstacle.h"

class Water : public Obstacle {
    public:
        Water(double x, double y, double width = 50, double height = 30, double angle = 0, double zIndex = 0, SDL_Texture* texture = Game::textures.at("water.png"));

        void activeAction(Car* car) override;
};

#endif //WATER_H
