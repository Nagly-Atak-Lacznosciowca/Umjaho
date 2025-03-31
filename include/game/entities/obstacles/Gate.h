#ifndef GATE_H
#define GATE_H

#include "game/Game.h"
#include "game/entities/obstacles/Obstacle.h"

class Gate : public Obstacle {
    public:
        Gate(double x, double y, double width = 25, double height = 200, double angle = 0, double zIndex = 0, SDL_Texture* texture = Game::textures.at("gate-closed.bmp"));
        bool isOpen = false;

        void passiveAction() override;
};

#endif //GATE_H
