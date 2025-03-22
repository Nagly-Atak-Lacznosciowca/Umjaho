//
// Created by oskar on 22.02.2025.
//

#ifndef UMJAHO_GAME_H
#define UMJAHO_GAME_H

#include <queue>
#include <functional>
#include <map>
#include <string>

#include "engine/Renderer.h"
#include "entity/Car.h"
#include "engine/scenes/SceneManager.h"

class Game {
public:
    Game();
    ~Game();
    // both values in ns
    unsigned long long lastTick = 0;
    unsigned long long deltaTime = 0;
    Renderer renderer;
    std::queue<void(*)()> gameQueue;

    static bool checkSpeedControls();
    static bool checkTurnControls();

    static bool checkElementCollision(SceneElement *car1, SceneElement *car2);

    static std::map<std::string, SDL_Texture*> textures;

    SceneManager sceneManager;

    void init();

private:
};

#endif //UMJAHO_GAME_H
