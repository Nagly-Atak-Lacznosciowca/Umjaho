#include "game/entities/obstacles/Gate.h"

#include "game/Game.h"

Gate::Gate(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture* texture) : Obstacle(x, y, width, height, angle, zIndex, texture) {
    isCollidable = true;
}

void Gate::passiveAction() {
    // temporeri
    // open and close the gate every 2 seconds
    if (SDL_GetTicks() % 2000 < 1000) {
        isOpen = true;
    }
    else {
        isOpen = false;
    }

    if (isOpen) {
        // open the gate
        this->texture = nullptr;
        this->isCollidable = false;
    }
    else {
        // close the gate
        this->texture = Game::textures.at("curb.bmp");
        this->isCollidable = true;
    }
}