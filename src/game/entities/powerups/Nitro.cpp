#include "game/entities/powerups/Nitro.h"
#include "game/Event.h"

Nitro::Nitro(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture* texture): PowerUp(x,y,width,height,angle,zIndex, texture){};

void Nitro::action(Player *player) {
    player->nitroCharges += 1;
    SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_NITRO_COLLECT});
}