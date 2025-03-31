#ifndef UMJAHO_OBSTACLE_H
#define UMJAHO_OBSTACLE_H
#include "engine/scenes/SceneElement.h"
#include "game/entities/Car.h"

class Obstacle : public SceneElement {
    public:
        Obstacle(double x, double y, double width = 50, double height = 50, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
        ~Obstacle() override;

        virtual void passiveAction();           // Standard action executed for the whole time, e.g. gate opening and closing
        virtual void activeAction(Car* car);    // Action executed when the player collides with the obstacle, e.g. mine explosion
};

#endif //UMJAHO_OBSTACLE_H