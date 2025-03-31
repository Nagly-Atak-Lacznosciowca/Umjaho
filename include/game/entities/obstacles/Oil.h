#ifndef OIL_H
#define OIL_H

#include "game/Game.h"
#include "game/entities/obstacles/Obstacle.h"

class Oil : public Obstacle {
    public:
        Oil(double x, double y, double width = 40, double height = 40, double angle = 0, double zIndex = 0, SDL_Texture* texture = Game::textures.at("oil.png"));

        void activeAction(Car* car) override;
};

#endif //OIL_H
