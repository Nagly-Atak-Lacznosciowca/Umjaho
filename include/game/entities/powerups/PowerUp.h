#ifndef UMJAHO_POWERUP_H
#define UMJAHO_POWERUP_H
#include "engine/scenes/SceneElement.h"
#include "game/Game.h"
#include "game/entities/Player.h"

class PowerUp : public SceneElement{
    public:
        PowerUp(double x, double y, double width = 40, double height = 40, double angle = 0, double zIndex = 0, SDL_Texture* texture = Game::textures.at("powerup.png"));
        ~PowerUp() override = default;

        void collide(SceneElement* element) override;
        virtual void action(Player* player);
};

#endif //UMJAHO_POWERUP_H
