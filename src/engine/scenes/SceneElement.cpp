#include <stdexcept>
#include "engine/scenes/SceneElement.h"
#include "game/Game.h"

SceneElement::SceneElement(const double x, const double y, const double width, const double height, const double angle, const double zIndex, SDL_Texture* texture) : x(x), y(y), width(width), height(height), angle(angle), zIndex(zIndex), texture(texture) {}

/// Given car's position, size and angle, computes its vertices if it was rotated by that angle
/// FIX: Would be better to rotate from wheels' position instead of center
SDL_FPoint *SceneElement::getPoints() const {
	// If car's angle is 0, it's rotated sideways, facing right.
	// Thus, length and not width is added to x-es, same with y-s, but with width instead

    SDL_FPoint center = SDL_FPoint(x + width / 2, y + height / 2);
	const SDL_FPoint points[] = { SDL_FPoint(x, y),
                                  SDL_FPoint(x + width, y),
                                  SDL_FPoint(x + width, y + height),
                                  SDL_FPoint(x, y + height) };
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

void SceneElement::render()
{
	auto rect = SDL_FRect{ static_cast<float>(this->x),
                           static_cast<float>(this->y),
                           static_cast<float>(this->width),
                           static_cast<float>(this->height) };

//    SDL_FPoint pivot = { 0.0f, 0.0f };
    SDL_RenderTextureRotated(Game::renderer.SDLRenderer, texture, nullptr, &rect, -angle * (180.0f / SDL_PI_F), nullptr, SDL_FLIP_NONE);

#ifdef DEBUG
    const auto points = getPoints();
    SDL_RenderLines(Game::renderer.SDLRenderer, points, 5);
    delete[] points;
#endif
}

SceneElement::~SceneElement() {
}

void SceneElement::	collide(SceneElement *element) {
}
