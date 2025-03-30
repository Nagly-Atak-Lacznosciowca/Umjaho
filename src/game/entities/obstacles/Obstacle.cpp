#include "game/entities/obstacles/Obstacle.h"
#include <stdexcept>

Obstacle::Obstacle(const double x, const double y, const double width, const double height, const double angle, const double zIndex, SDL_Texture* texture) : SceneElement(x, y, width, height, angle, zIndex, texture) {
    isCollidable = true;
}

void Obstacle::passiveAction() {
    throw std::runtime_error("Not implemented");
}

void Obstacle::activeAction() {
    throw std::runtime_error("Not implemented");
}