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
    int width = 250;
    int length = 500;
    SDL_Texture* texture = nullptr;

    Car(double x, double y, double z, SDL_Texture* texture);
    void move(const double deltas[]);
    void render(Renderer* renderer) const;
    SDL_FPoint *getRotatedPoints() const;
};

#endif //UMJAHO_CAR_H
