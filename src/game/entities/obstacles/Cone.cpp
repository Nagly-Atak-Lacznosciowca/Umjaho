#include "game/entities/obstacles/Cone.h"

#include "game/entities/Car.h"

Cone::Cone(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture* texture) : Obstacle(x, y, width, height, angle, zIndex, texture) {
    isCollidable = true;
}

void Cone::activeAction(Car* car) {
    car->speed = 0.5;
    Cone::~Cone();
}