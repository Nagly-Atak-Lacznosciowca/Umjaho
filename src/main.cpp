#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "engine/Renderer.h"
#include "game/Game.h"
#include "game/Event.h"

Renderer *renderer = new Renderer();
Game *game = new Game();

[[maybe_unused]] SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "pl.krakow.pl.umjaho");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 640, 480, SDL_WINDOW_RESIZABLE, &renderer->window, &renderer->renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

[[maybe_unused]] SDL_AppResult SDL_AppIterate(void *appstate)
{
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const auto red = (float) (0.5 + 0.5 * SDL_sin(now));
    const auto green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const auto blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer->renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    // game.tick();

    /* clear the window to the draw color. */
    SDL_RenderClear(renderer->renderer);

//    while(SDL_P)

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer->renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

[[maybe_unused]] SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type) {
        case (SDL_EVENT_QUIT):
            return SDL_APP_SUCCESS;
        case (SDL_EVENT_KEY_DOWN):
            SDL_Log("Key Down");
            break;
        case (SDL_EVENT_KEY_UP):
            SDL_Log("Key Up");
            break;
        case (SDL_EVENT_MOUSE_BUTTON_DOWN):
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
            }
            break;
        case (Event::CUSTOM_EVENT):
            SDL_Log("Custom event");
            break;
        case (Event::CUSTOM_EVENT_ZWEI):
            SDL_Log("Custom event ga");
            break;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

[[maybe_unused]] void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
    SDL_Log("cycki");
}