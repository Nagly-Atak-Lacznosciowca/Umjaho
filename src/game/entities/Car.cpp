#include "game/entity/Car.h"
#include "SDL3/SDL.h"
#include "engine/Renderer.h"
#include "array"

// length 3 array [dx, dy, dz]
void Car::move() {
    double forwardVector[] = {
        this->x + this->speed * SDL_cos(-this->angle),    // Formula for vector rotation or something
        this->y + this->speed * SDL_sin(-this->angle),    // Beware of the minus sign :(((
        this->z
    };
    this->x = forwardVector[0];
    this->y = forwardVector[1];
    this->z = forwardVector[2];
}

Car::Car(const double x, const double y, const double z, SDL_Texture* texture) : SceneElement(), x(x), y(y), z(z), texture(texture) {}

void Car::render(Renderer* renderer) const {
    auto car = SDL_FRect{ static_cast<float>(this->x), static_cast<float>(this->y), static_cast<float>(this->length), static_cast<float>(this->width) };

    const auto points = getRotatedPoints();
    const SDL_FPoint center = { (points[1].x + points[3].x) / 2, (points[1].y + points[3].y) / 2 };
    SDL_RenderTextureRotated(renderer->SDLRenderer, texture, nullptr, &car, -angle * (180.0f / SDL_PI_F), nullptr, SDL_FLIP_NONE);

    // SDL_RenderRect(renderer->SDLRenderer, &car);
    SDL_RenderLines(renderer->SDLRenderer, points, 5);

    delete points;
}

/// Given car's position, size and angle, computes its vertices if it was rotated by that angle
/// FIX: Would be better to rotate from wheels' position instead of center
SDL_FPoint *Car::getRotatedPoints() const {
    // If car's angle is 0, it's rotated sideways, facing right.
    // Thus, length and not width is added to x-es, same with y-s, but with width instead

    SDL_FPoint center = SDL_FPoint((x + x + length) / 2, (y + y + width) / 2);
    const SDL_FPoint points[] = { SDL_FPoint(x, y), SDL_FPoint(x + length, y), SDL_FPoint(x + length, y + width), SDL_FPoint(x, y + width) };
    auto* result = new SDL_FPoint[5];

    const float sin = SDL_sin(-angle);
    const float cos = SDL_cos(-angle);

    for (int i = 0; i < 4; i++) {
        result[i] = SDL_FPoint(
            cos * (points[i].x - center.x) - sin * (points[i].y - center.y) + center.x,
            sin * (points[i].x - center.x) + cos * (points[i].y - center.y) + center.y
        );
    }
    result[4] =  result[0];

    return result;
}

void Car::decelerate() {
    if (speed > 0) {
        speed-=acceleration;
    }
    else if (speed < 0) {
        speed+=acceleration;
    }
    if (speed > -this->acceleration*2 && speed < this->acceleration*2) {
        SDL_Log("chuj");
        speed = 0;
    }
}
void Car::accelerate() {
    speed+=acceleration;
}

void Car::reverse() {
    speed-=acceleration/2;
}