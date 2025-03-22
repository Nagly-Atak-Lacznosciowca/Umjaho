#ifndef LEVEL1_H
#define LEVEL1_H
#include "engine/scenes/Scene.h"
#include "game/entity/Opponent.h"
#include "game/entity/Player.h"

class Level1 : public Scene {
    public:
        Level1();
        void logic() override;
        void handleEvent(SDL_Event* event) override;
        Player *player = nullptr;
        Opponent *opponent = nullptr;
};

#endif //LEVEL1_H
