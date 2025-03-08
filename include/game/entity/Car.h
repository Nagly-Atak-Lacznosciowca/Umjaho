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

    Car(double x, double y, double z);
    void move(const double deltas[]);
    void render(Renderer* renderer);
    std::array<SDL_FPoint, 5> getRotatedPoints();
};

#endif //UMJAHO_CAR_H
