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

    static bool checkSpeedControls();
    static bool checkTurnControls();
		
	static SDL_FPoint* getIntersection(SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3, SDL_FPoint p4);
    static SDL_FPoint* checkElementCollision(SceneElement *elem1, SceneElement *elem2);

    static std::map<std::string, SDL_Texture*> textures;

    SceneManager sceneManager;

    void init();

private:
};

#endif //UMJAHO_GAME_H
