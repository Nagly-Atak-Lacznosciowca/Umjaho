#include "engine/scenes/SceneElement.h"

SceneElement::SceneElement(const double x, const double y, const double width, const double height, const double angle, const double zIndex, SDL_Texture* texture) : x(x), y(y), width(width), height(height), angle(angle), zIndex(zIndex), texture(texture) {}

/// Given car's position, size and angle, computes its vertices if it was rotated by that angle
/// FIX: Would be better to rotate from wheels' position instead of center
SDL_FPoint *SceneElement::getPoints() const {
	// If car's angle is 0, it's rotated sideways, facing right.
	// Thus, length and not width is added to x-es, same with y-s, but with width instead
	
	SDL_FPoint center = SDL_FPoint((x + x + height) / 2, (y + y + width) / 2);
	const SDL_FPoint points[] = { SDL_FPoint(x, y), SDL_FPoint(x + height, y), SDL_FPoint(x + height, y + width), SDL_FPoint(x, y + width) };
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

void SceneElement::render(Renderer &renderer) const
{
	auto rect = SDL_FRect{ static_cast<float>(this->x), static_cast<float>(this->y), static_cast<float>(this->height), static_cast<float>(this->width) };
	SDL_RenderRect(renderer.SDLRenderer, &rect);    // Non-rotated hitbox, comment out when collisions are done
	
	const auto points = getPoints();
	const SDL_FPoint center = { (points[1].x + points[3].x) / 2, (points[1].y + points[3].y) / 2 };
	SDL_RenderTextureRotated(renderer.SDLRenderer, texture, nullptr, &rect, -angle * (180.0f / SDL_PI_F), nullptr, SDL_FLIP_NONE);
	
	SDL_RenderLines(renderer.SDLRenderer, points, 5);
	
	delete points;
}