#define SDL_MAIN_USE_CALLBACKS 1

#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_hints.h>

#include "engine/Renderer.h"
#include "engine/scenes/scenes/Level1.h"
#include "game/Game.h"
#include "game/Event.h"
#include "game/entities/Car.h"
#include "game/entities/Opponent.h"
#include "game/entities/Player.h"

auto game = new Game();

[[maybe_unused]] SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_SetAppMetadata("Umjaho", "1.0", "tl.krakow.pl.umjaho");

    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /// changing width/height in current version will destroy buttons on `Menu`
    if (!SDL_CreateWindowAndRenderer("Umjaho: Racing for True Racists", 1600, 900,
        0, &Game::renderer.SDLWindow, &Game::renderer.SDLRenderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    TTF_Init();
	
    game->init();

    return SDL_APP_CONTINUE;    // Carry on with the program
}


[[maybe_unused]] SDL_AppResult SDL_AppIterate(void* appstate) {
    const Uint64 now = SDL_GetTicksNS();

    game->deltaTime = now - game->lastTick;
    game->lastTick = now;

    SDL_SetRenderDrawColor(Game::renderer.SDLRenderer, 0, 0, 0, 1);
    SDL_RenderClear(Game::renderer.SDLRenderer);
    SDL_SetRenderDrawColor(Game::renderer.SDLRenderer, 255, 100, 0, 1);

    static Uint64 lastActionTime = 0;
    const Uint64 actionInterval = 10000000; // 10ms interval

    if (now - lastActionTime > actionInterval) {
        //current scene game tick
	    Game::sceneManager.currentScene()->logic();

        lastActionTime = now;
    }
  
    //scene render
	Game::sceneManager.currentScene()->render();
	
    // draws FPS
    const float fps = 1000000000.0f / game->deltaTime;
    SDL_SetRenderDrawColor(Game::renderer.SDLRenderer, 255, 255, 255, 255);
    SDL_RenderDebugText(Game::renderer.SDLRenderer, 0, 0, ("FPS: " + std::to_string(fps)).c_str());
    // SDL_RenderDebugText(Game::renderer.SDLRenderer, 0, 10, ("Speed: " + std::to_string(player->speed)).c_str());
    // SDL_RenderDebugText(Game::renderer.SDLRenderer, 0, 20, ("Angle: " + std::to_string(player->angle)).c_str());
    // SDL_RenderDebugText(Game::renderer.SDLRenderer, 0, 30, ("Turn radius: " + std::to_string(player->turnAngle)).c_str());
    // SDL_RenderDebugText(Game::renderer.SDLRenderer, 0, 40, ("Max turn radius: " + std::to_string(player->maxTurnAngle)).c_str());
    SDL_RenderPresent(Game::renderer.SDLRenderer);

    return SDL_APP_CONTINUE; /* carry on with the program! */
}


[[maybe_unused]] SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {

    switch (event->type) {

        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            float x, y;
            SDL_GetMouseState(&x, &y);
            SDL_Log("Click position: %f %f", x, y);
            break;
        }

        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;

        default: {
            break;
        }
    }
    Game::sceneManager.currentScene()->handleEvent(event);

    return SDL_APP_CONTINUE;
}


[[maybe_unused]] void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    TTF_Quit();
}
