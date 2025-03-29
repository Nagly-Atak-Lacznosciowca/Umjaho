#ifndef UMJAHO_LEVEL_H
#define UMJAHO_LEVEL_H

#include "engine/scenes/Scene.h"
#include "game/entities/Player.h"
#include "game/entities/Opponent.h"

class Level: public Scene{
public:
    Level() = default;
    void logic() override;
    void handleEvent(SDL_Event* event) override;
    Player *player = nullptr;
    Opponent* opponents[4] = {};
};

#endif //UMJAHO_LEVEL_H
