#define SDL_MAIN_USE_CALLBACKS 1

#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_render.h>

#include "engine/Renderer.h"
#include "game/Game.h"
#include "game/Event.h"
#include "game/entity/Car.h"

auto game = new Game();
auto car = new Car(100, 100, 1);

[[maybe_unused]] SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "pl.krakow.pl.umjaho");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 800, 540, SDL_WINDOW_RESIZABLE,
                                     &game->renderer.SDLWindow, &game->renderer.SDLRenderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

void function() {
    SDL_Log("Hello World!");
}

[[maybe_unused]] SDL_AppResult SDL_AppIterate(void* appstate) {
    const Uint64 now = SDL_GetTicksNS();

    game->deltaTime = now - game->lastTick;
    game->lastTick = now;

    for (; !game->gameQueue.empty(); game->gameQueue.pop()) {
        game->gameQueue.front()();
    }


    // if (game->deltaTime != 0) SDL_Log("%s", std::to_string(1000000000.0f / game->deltaTime).c_str());    // logs FPS


    SDL_SetRenderDrawColor(game->renderer.SDLRenderer, 0, 0, 0, 1);
    SDL_RenderClear(game->renderer.SDLRenderer);
    SDL_SetRenderDrawColor(game->renderer.SDLRenderer, 255, 100, 0, 1);

    car->render(&game->renderer);
    SDL_RenderPresent(game->renderer.SDLRenderer);


    // SDL_RenderDebugText(game->renderer.SDLRenderer, 0, 0, std::to_string(1000.0 / game->deltaTime).c_str());

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

[[maybe_unused]] SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;

    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
        // Temporary car steering, TO DO make it smoooooth
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
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        SDL_Log("Pressed %d", event->button.button);
        switch (event->button.button) {
        case SDL_BUTTON_LEFT: {
            auto custom_event = SDL_Event{Event::CUSTOM_EVENT};
            SDL_PushEvent(&custom_event);
            break;
        }
        case SDL_BUTTON_RIGHT: {
            auto custom_event = SDL_Event{Event::CUSTOM_EVENT_ZWEI};
            SDL_PushEvent(&custom_event);
            break;
        }
        default: {
            break;
        }
        }
        break;
    case Event::CUSTOM_EVENT: {
        SDL_Log("Custom event");
        break;
    }
    case Event::CUSTOM_EVENT_ZWEI: {
        SDL_Log("Custom event ga");
        break;
    }

    case Event::CUSTOM_EVENT_CAR_ROTATE_LEFT: {
        car->angle += 0.1;
        break;
    }
    case Event::CUSTOM_EVENT_CAR_ROTATE_RIGHT: {
        car->angle -= 0.1;
        break;
    }

    case Event::CUSTOM_EVENT_CAR_MOVE_FORWARD: {
        // Move car in the direction it's facing
        double forwardVector[] = {car->x + 10 * SDL_cos(-car->angle), car->y + 10 * SDL_sin(-car->angle), car->z};  // Formula for vector rotation or something
        car->move(forwardVector);
        break;
    }
    case Event::CUSTOM_EVENT_CAR_MOVE_BACKWARD: {
        double backwardVector[] = {car->x - 10 * SDL_cos(-car->angle), car->y - 10 * SDL_sin(-car->angle), car->z}; // Beware of the minus sign :(((
        car->move(backwardVector);
        break;
    }

    default: {
        break;
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Aplikacja zostanie roztrzaskana");
        SDL_Quit();
    }
    }

    return SDL_APP_CONTINUE;
}

[[maybe_unused]] void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    SDL_Log("cycki");
}
