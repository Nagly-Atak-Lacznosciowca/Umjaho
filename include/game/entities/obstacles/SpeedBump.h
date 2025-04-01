#ifndef SPEEDBUMP_H
#define SPEEDBUMP_H

#include "game/Game.h"
#include "game/entities/obstacles/Obstacle.h"

class SpeedBump : public Obstacle {
    public:
        SpeedBump(double x, double y, double width = 75, double height = 15, double angle = 0, double zIndex = 0, SDL_Texture* texture = Game::textures.at("speedbump.png"));

        void activeAction(Car* car) override;
};

#endif //SPEEDBUMP_H
