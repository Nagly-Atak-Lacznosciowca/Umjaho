#include <stdexcept>
#include "game/entities/powerups/PowerUp.h"
#include "game/Game.h"

PowerUp::PowerUp(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture): SceneElement(x,y,width,height,angle,zIndex,texture) {}

void PowerUp::collide(SceneElement *element) {
    if(auto car = dynamic_cast<Player*>(element)){
        Game::sceneManager.currentScene()->deleteElement(this);
        action(car);
    }
}

void PowerUp::action(Player* player) {
    throw std::runtime_error("Not implemented");
}