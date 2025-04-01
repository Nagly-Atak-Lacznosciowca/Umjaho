#include "game/entities/Bot.h"
#include "SDL3/SDL.h"
#include <cmath>
#include "game/Game.h"
#include "math/Vec2.h"

Bot::Bot(double x, double y, Player &player, std::vector<Bot *> &opponents, std::vector<SceneElement *> &contents, std::vector<Checkpoint *> &checkpoints,
         double zIndex,SDL_Texture *texture, double width, double length, double angle) : Car( x, y, 0, -1, width, length, angle, zIndex, texture), checkpoints(checkpoints), contents(contents), player(player), opponents(opponents) {

}

void Bot::update() {
    updateRays();

    for (const auto content : contents) {
        checkRayCollision(rays, content);
    }
    for (const auto checkpoint : checkpoints) {
        checkRayCollision(rays, checkpoint);
    }
    for (const auto opponent : opponents) {
        checkRayCollision(rays, opponent);
    }

    Vec2 vectorRays[7];
    Vec2 collidedVectorRays[7];

    for (int i = 0; i < 7; i++) {
        vectorRays[i] = {rays[i].direction.x - rays[i].origin.x, rays[i].direction.y - rays[i].origin.y};

    }

    if (rays[0].collides || rays[1].collides || rays[2].collides) {
        decelerate();
        angle += 0.02;
    } else if (rays[4].collides || rays[5].collides || rays[6].collides) {
        decelerate();
        angle -= 0.0;
        // turnLeft();
    } else if (rays[3].collides) {
        decelerate();
        // turnRight();
    } else {
        accelerate();
    }

    move();

}


void Bot::updateRays() {
    rays.clear();
    const float angleStep = M_PI / (rayCount - 1);

    const auto points = this->getPoints();
    const SDL_FPoint center = {
        ((points[1].x + points[3].x)/2),
        ((points[0].y + points[2].y)/2)
    };

    for (int i = 0; i < rayCount; i++) {
        // constexpr float c = 0.5; // steepness
        // const double scale = exp(-c * pow(i - (rayCount / 2), 2)); // modified normal distribution
        constexpr double scale = 1;

        const float rayAngle = static_cast<float>(-angle) + angleStep * i;
        Ray ray = {
            {
                static_cast<float>(center.x + 20 * cos(rayAngle)),
                static_cast<float>(center.y + 20 * sin(rayAngle))
            },
            {
                static_cast<float>(center.x + (75 * scale) * cos(rayAngle)),
                static_cast<float>(center.y + (75 * scale) * sin(rayAngle))
            },
        };
        rays.push_back(ray);
    }

    delete[] points;
}

void Bot::render() {
    SceneElement::render();
    const auto points = this->getPoints();

    for (const auto& [origin, direction, collides] : rays) {
        const SDL_FPoint line[2] = {origin, direction};

        if (collides) {
            SDL_Log("collides");
            SDL_SetRenderDrawColor(Game::renderer.SDLRenderer, 255, 0, 0, 255);
        } else {
            SDL_SetRenderDrawColor(Game::renderer.SDLRenderer, 255, 100, 0, 1);
        }

        SDL_RenderLines(Game::renderer.SDLRenderer, line, 2);
    }
    delete[] points;
}

void Bot::checkRayCollision(const std::vector<Ray>& rays, const SceneElement* element) {
    const auto points = element->getPoints();
    SDL_FPoint _ = {};

    // Check intersection with all 4 edges of the obstacle
    for (const auto& ray : rays) {
        if (ray.collides) {
            continue;
        }
        for (int i = 0; i < 4; i++) {
            if (Game::getIntersection(ray.origin, ray.direction, points[i], points[(i + 1) % 4], _)) {
                ray.collides = true;
            }
        }
    }

    delete[] points;
}

void Bot::collide(SceneElement* element) {
    Car::collide(element);
}

void Bot::logic() {
    // std::vector<SceneElement*> allElements;
}

