//
// Created by oskar on 22.02.2025.
//

#ifndef UMJAHO_EVENT_H
#define UMJAHO_EVENT_H

#include <SDL3/SDL_events.h>

namespace Event {
    enum Event {
        CUSTOM_EVENT = SDL_EVENT_USER + 1,
        CUSTOM_EVENT_CAR_ROTATE_LEFT,
        CUSTOM_EVENT_CAR_ROTATE_RIGHT,
        CUSTOM_EVENT_CAR_MOVE_FORWARD,
        CUSTOM_EVENT_CAR_MOVE_BACKWARD,
        CUSTOM_EVENT_CAR_NITRO_COLLECT,
        CUSTOM_EVENT_CAR_NITRO_USE,
    };
}

#endif //UMJAHO_EVENT_H
