#ifndef UMJAHO_PLAYER_H
#define UMJAHO_PLAYER_H

#include "engine/Renderer.h"
#include "game/entities/Car.h"
#include "game/entities/obstacles/Obstacle.h"

class Player : public Car {
    public:
        int nitroTimer = 0;
        bool nitroActive = false;
        int nitroCharges = 0;
        bool onFinishLine = false;
        Obstacle* heldObstacle = nullptr;
        
        void SetTexture();
        
        Player(double x, double y, double width = Car::WIDTH, double length = Car::LENGTH, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
};

#endif //UMJAHO_PLAYER_H
