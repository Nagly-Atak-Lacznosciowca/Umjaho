#include "game/entities/Bot.h"
#include "SDL3/SDL.h"
#include <cmath>
#include "game/Game.h"

Bot::Bot(double x, double y, Player &player, std::vector<Bot *> &opponents, std::vector<SceneElement *> &contents, std::vector<Checkpoint *> &checkpoints,
         double zIndex,SDL_Texture *texture, double width, double length, double angle) : Car( x, y, 0, -1, width, length, angle, zIndex, texture), checkpoints(checkpoints), contents(contents), player(player), opponents(opponents) {

}


void Bot::update() {
    rays.clear();
    SDL_Log("sakduk");
    speed = 1;
    angle += 0.05;
    move();
    float angleStep = M_PI / (rayCount - 1);
    SDL_Log("angle is %f", angle);

    for (int i = 0; i < rayCount; i++) {
        float rayAngle = static_cast<float>(-angle) + angleStep * i;
        Vec2 rayDir = {SDL_cos(rayAngle), SDL_sin(rayAngle)};
        rays.push_back(rayDir);
    }
}

void Bot::render() {
    SceneElement::render();
    auto points = this->getPoints();
    SDL_FPoint frontCenter = {
        (points[2].x + points[3].x)/2,
        (points[2].y + points[3].y)/2
    };
    for (const Vec2& ray : rays) {
        Vec2 endPoint = Vec2 {frontCenter.x, frontCenter.y} + (ray * 25); // 25 = max ray dist
        SDL_RenderLine(Game::renderer.SDLRenderer, frontCenter.x, frontCenter.y, endPoint.x, endPoint.y);
    }
    delete[] points;
}
