#include "game/entities/obstacles/Obstacle.h"
#include <stdexcept>

Obstacle::Obstacle(const double x, const double y, const double width, const double height, const double angle, const double zIndex, SDL_Texture* texture) : SceneElement(x, y, width, height, angle, zIndex, texture) {
    isCollidable = true;
}

Obstacle::~Obstacle() {
    this->texture = nullptr;
    this->isCollidable = false;
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}

void Obstacle::passiveAction() {
    throw std::runtime_error("Not implemented");
}

void Obstacle::activeAction(Car* car) {
    throw std::runtime_error("Not implemented");
}

void Obstacle::countdownToDestroy() {
    if (timeToDestroy > 10) {
        timeToDestroy -= 10;
    }
    else if (timeToDestroy > 0) {
        timeToDestroy = 0;
    }
    if (timeToDestroy == 0) {
        this->~Obstacle();
    }
}