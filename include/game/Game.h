//
// Created by oskar on 22.02.2025.
//

#ifndef UMJAHO_GAME_H
#define UMJAHO_GAME_H

#include <queue>
#include <functional>

#include "engine/Renderer.h"

class Game {
public:
    Game();
    ~Game();
    // both values in ns
    unsigned long long lastTick = 0;
    unsigned long long deltaTime = 0;
    Renderer renderer;
    std::queue<void(*)()> gameQueue;
private:
};

#endif //UMJAHO_GAME_H
