#include "game/entities/surfaces/FinishLine.h"

#include "engine/scenes/scenes/Level.h"
#include "game/Game.h"
#include "game/entities/Player.h"

FinishLine::FinishLine(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture): Surface(x, y, width, height, angle, zIndex, texture) {}

void FinishLine::collide(SceneElement* element) {
    if (auto player = dynamic_cast<Player*>(element)) {
        if (Game::checkSurfaceIntersection(player, this)) {
            action(player);
        }
    }
}

void FinishLine::action(Car* car) {
    auto player = dynamic_cast<Player*>(car);
    if (player->onFinishLine) return;
    player->onFinishLine = true;
}
