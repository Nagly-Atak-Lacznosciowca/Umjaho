#ifndef UMJAHO_NITRO_H
#define UMJAHO_NITRO_H
#include "game/entities/powerups/PowerUp.h"
#include "game/Game.h"
#include <cmath>

class Nitro: public PowerUp{
public:
    Nitro(double x, double y, double width = 55, double height = 20, double angle = M_PI / 4, double zIndex = 0, SDL_Texture* texture = Game::textures.at("nitro3.png"));
    void action(Player* player) override;
};

#endif //UMJAHO_NITRO_H
