#define SDL_MAIN_USE_CALLBACKS 1

#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_hints.h>

#include "engine/Renderer.h"
#include "game/Game.h"
#include "game/Event.h"
#include "game/entity/Car.h"
#include "game/entity/Opponent.h"
#include "game/entity/Player.h"


auto game = new Game();
Player *player = nullptr;
Opponent *opponent = nullptr;

[[maybe_unused]] SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_SetAppMetadata("Umjaho", "1.0", "tl.krakow.pl.umjaho");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Umjaho: Racing for True Racists", 800, 540,
        SDL_WINDOW_RESIZABLE, &game->renderer.SDLWindow, &game->renderer.SDLRenderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    SDL_Surface* playerSurface = SDL_LoadBMP("../assets/car-blue-regular.bmp");
    SDL_Log("SDL_CreateTextureFromSurface: %s", SDL_GetError());
    SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(game->renderer.SDLRenderer, playerSurface);
    SDL_SetTextureScaleMode(playerTexture, SDL_SCALEMODE_NEAREST);
    player = new Player(10, 10, 1, playerTexture);

    SDL_Surface* opponentSurface = SDL_LoadBMP("../assets/car-red-regular.bmp");
    SDL_Log("SDL_CreateTextureFromSurface: %s", SDL_GetError());
    SDL_Texture* opponentTexture = SDL_CreateTextureFromSurface(game->renderer.SDLRenderer, opponentSurface);
    SDL_SetTextureScaleMode(opponentTexture, SDL_SCALEMODE_NEAREST);
    opponent = new Opponent(300, 200, 1, opponentTexture);


    return SDL_APP_CONTINUE;    // Carry on with the program
}


[[maybe_unused]] SDL_AppResult SDL_AppIterate(void* appstate) {
    const Uint64 now = SDL_GetTicksNS();

    game->deltaTime = now - game->lastTick;
    game->lastTick = now;

    for (; !game->gameQueue.empty(); game->gameQueue.pop()) {
        game->gameQueue.front()();
    }

    SDL_SetRenderDrawColor(game->renderer.SDLRenderer, 0, 0, 0, 1);
    SDL_RenderClear(game->renderer.SDLRenderer);
    SDL_SetRenderDrawColor(game->renderer.SDLRenderer, 255, 100, 0, 1);

    static Uint64 lastActionTime = 0;
    const Uint64 actionInterval = 10000000; // 10ms interval

    if (now - lastActionTime > actionInterval) {
        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A]) {
            auto custom_event = SDL_Event{Event::CUSTOM_EVENT_CAR_ROTATE_LEFT};
            SDL_PushEvent(&custom_event);
        }
        else if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D]) {
            auto custom_event = SDL_Event{Event::CUSTOM_EVENT_CAR_ROTATE_RIGHT};
            SDL_PushEvent(&custom_event);
        }

        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W]) {
            auto custom_event = SDL_Event{Event::CUSTOM_EVENT_CAR_MOVE_FORWARD};
            SDL_PushEvent(&custom_event);
        }
        else if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S]) {
            auto custom_event = SDL_Event{Event::CUSTOM_EVENT_CAR_MOVE_BACKWARD};
            SDL_PushEvent(&custom_event);
        }

        if (!Game::checkSpeedControls()) {
            player->decelerate();
        }
        if (!Game::checkTurnControls()) {
            player->straighten();
        }

        lastActionTime = now;
        player->move();

        if (Game::checkCarCollision(player, opponent)) {
            SDL_Log("Car collision detected on %d", now);
        }
    }

    player->render(&game->renderer);
    opponent->render(&game->renderer);

    // draws FPS
    const float fps = 1000000000.0f / game->deltaTime;
    SDL_SetRenderDrawColor(game->renderer.SDLRenderer, 255, 255, 255, 255);
    SDL_RenderDebugText(game->renderer.SDLRenderer, 0, 0, ("FPS: " + std::to_string(fps)).c_str());
    SDL_RenderDebugText(game->renderer.SDLRenderer, 0, 10, ("Speed: " + std::to_string(player->speed)).c_str());
    SDL_RenderDebugText(game->renderer.SDLRenderer, 0, 20, ("Angle: " + std::to_string(player->angle)).c_str());
    SDL_RenderDebugText(game->renderer.SDLRenderer, 0, 30, ("Turn radius: " + std::to_string(player->turnAngle)).c_str());
    SDL_RenderDebugText(game->renderer.SDLRenderer, 0, 40, ("Max turn radius: " + std::to_string(player->maxTurnAngle)).c_str());
    SDL_RenderPresent(game->renderer.SDLRenderer);

    return SDL_APP_CONTINUE; /* carry on with the program! */
}


[[maybe_unused]] SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {

    switch (event->type) {
        case Event::CUSTOM_EVENT_CAR_ROTATE_LEFT: {
            player->turnLeft();
            break;
        }
        case Event::CUSTOM_EVENT_CAR_ROTATE_RIGHT: {
            player->turnRight();
            break;
        }

        case Event::CUSTOM_EVENT_CAR_MOVE_FORWARD: {
            player->accelerate();
            break;
        }
        case Event::CUSTOM_EVENT_CAR_MOVE_BACKWARD: {
            if (player->speed > 0) player->brake();
            else player->reverse();
            break;
        }

        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;

        default: {
            break;
        }
    }

    return SDL_APP_CONTINUE;
}


[[maybe_unused]] void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    SDL_Log("cycki");
}
