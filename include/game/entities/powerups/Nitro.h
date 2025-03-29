#ifndef UMJAHO_NITRO_H
#define UMJAHO_NITRO_H
#include "game/entities/powerups/PowerUp.h"

class Nitro: public PowerUp{
public:
    Nitro(double x, double y, double width = 50, double height = 50, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
    void action(Player* player) override;
};

#endif //UMJAHO_NITRO_H
