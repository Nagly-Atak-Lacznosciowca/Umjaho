#ifndef UMJAHO_BOT_H
#define UMJAHO_BOT_H

#include "engine/Renderer.h"
#include "game/entities/Car.h"
#include "Player.h"
#include "math/Vec2.h"

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
        std::vector<Vec2> rays;
        int rayCount = 7;
        virtual void update();
        virtual double evaluateTurn(double) = 0;
        void render() override;

};

#endif //UMJAHO_BOT_H
