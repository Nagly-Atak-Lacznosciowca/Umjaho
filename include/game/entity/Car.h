#ifndef UMJAHO_CAR_H
#define UMJAHO_CAR_H

#include "engine/scenes/SceneElement.h"
#include "engine/Renderer.h"

class Car : SceneElement {
public:
    double x = 0;
    double y = 0;
    double z = 0;
    double angle = 0; // In radians
    int width = 50;
    int length = 100;
    SDL_Texture* texture = nullptr;
    float acceleration = 0.1f;
    float speed = 0.0f;

    Car(double x, double y, double z, SDL_Texture* texture);
    void move();
    void decelerate();
    void accelerate();
    void reverse();
    void render(Renderer* renderer) const;
    SDL_FPoint *getRotatedPoints() const;
};

#endif //UMJAHO_CAR_H
