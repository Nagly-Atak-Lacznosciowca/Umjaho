#ifndef UMJAHO_BOT_H
#define UMJAHO_BOT_H

#include "game/entities/Car.h"
#include "Player.h"
#include "math/Ray.h"

class Bot : public Car {
    public:
        Bot(double x,
            double y,
            Player &player,
            std::vector<Bot *> &opponents,
            std::vector<SceneElement *> &contents,
            std::vector<Checkpoint *> &checkpoints,
            double zIndex = 0,
            SDL_Texture *texture = nullptr,
            double width = Car::WIDTH,
            double length = Car::LENGTH,
            double angle = 0);

        std::vector<Checkpoint *>& checkpoints;
        std::vector<SceneElement *>& contents;
        Player& player;
        std::vector<Bot *> opponents;
        std::vector<Ray> rays;
        int rayCount = 7;
        virtual void update();
        void updateRays();
        virtual double evaluateTurn(double) = 0;
        void render() override;
        static void checkRayCollision(const std::vector<Ray>& rays, const SceneElement* element);
        void collide(SceneElement* element) override;
        void logic();
};

#endif //UMJAHO_BOT_H
