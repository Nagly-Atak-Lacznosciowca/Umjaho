#ifndef UMJAHO_BOT_H
#define UMJAHO_BOT_H

#include "engine/Renderer.h"
#include "game/entities/Car.h"

class Bot : public Car {
    public:
        Bot(double x, double y, double width = Car::WIDTH, double length = Car::LENGTH, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);

        void update();
        double evaluateTurn(double testTurn);

};

#endif //UMJAHO_BOT_H
