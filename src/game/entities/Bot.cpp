#include "game/entities/Bot.h"
#include "SDL3/SDL.h"
#include <cmath>
#include "game/Game.h"

Bot::Bot(double x, double y, Player &player, std::vector<Bot *> &opponents, std::vector<SceneElement *> &contents, std::vector<Checkpoint *> &checkpoints,
         double zIndex,SDL_Texture *texture, double width, double length, double angle) : Car(
                 x,
                 y,
                 0,
                 -1,
                 width,
                 length,
                 angle,
                 zIndex,
                 texture), checkpoints(checkpoints), contents(contents), player(player), opponents(opponents) {
    float angleStep = M_PI / (rayCount - 1);

    for (int i = 0; i < rayCount; i++) {
        float rayAngle = static_cast<float>(angle) + (static_cast<float>(i) - (static_cast<float>(rayCount) / 2)) * angleStep;
        Vec2 rayDir = {SDL_cos(rayAngle), SDL_sin(rayAngle)};
        rays.push_back(rayDir);
    }
}


void Bot::update() {
    SDL_Log("sakduk");
    speed = 1;
    angle += 0.05;
    move();

}

void Bot::render() {
    SceneElement::render();
    for (const Vec2& ray : rays) {
        Vec2 endPoint = Vec2 {x, y} + (ray * 25); // 25 = max ray dist
        SDL_RenderLine(Game::renderer.SDLRenderer, this->x, this->y, endPoint.x, endPoint.y);
    }
}
