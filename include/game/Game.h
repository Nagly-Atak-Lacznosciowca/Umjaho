//
// Created by oskar on 22.02.2025.
//

#ifndef UMJAHO_GAME_H
#define UMJAHO_GAME_H

#include <queue>
#include <functional>

class Game {
    std::queue<std::function<void()>> gameQueue;
};

#endif //UMJAHO_GAME_H
