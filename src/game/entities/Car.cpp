#include "game/entity/Car.h"
#include "SDL3/SDL.h"
#include "engine/Renderer.h"
#include "array"

// length 3 array [dx, dy, dz]
void Car::move(const double deltas[]) {
    this->x = deltas[0];
    this->y = deltas[1];
    this->z = deltas[2];
}

Car::Car(double x, double y, double z) : x(x), y(y), z(z) {}

void Car::render(Renderer* renderer) {
    auto car = SDL_FRect{ static_cast<float>(this->x), static_cast<float>(this->y), static_cast<float>(this->length), static_cast<float>(this->width) };

    const auto points = getRotatedPoints();

    // SDL_RenderRect(renderer->SDLRenderer, &car);
    SDL_RenderLines(renderer->SDLRenderer, points.data(), 5);
}

/// Given car's position, size and angle, computes its vertices if it was rotated by that angle
/// FIX: Would be better to rotate from wheels' position instead of center
std::array<SDL_FPoint, 5> Car::getRotatedPoints() {
    // If car's angle is 0, it's rotated sideways, facing right.
    // Thus, length and not width is added to x-es, same with y-s, but with width instead

    SDL_FPoint center = SDL_FPoint((x + x + length) / 2, (y + y + width) / 2);
    std::array<SDL_FPoint, 4> points = { SDL_FPoint(x, y), SDL_FPoint(x + length, y), SDL_FPoint(x + length, y + width), SDL_FPoint(x, y + width) };
    std::array<SDL_FPoint, 5> result = std::array<SDL_FPoint, 5>();

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