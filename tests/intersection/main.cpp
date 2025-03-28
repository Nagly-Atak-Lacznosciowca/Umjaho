#include <iostream>
#include <cassert>
#include <iomanip>

#include "game/Game.h"

float round(float v, int decimal) {
	auto rounder = SDL_powf(1.0f, (float)decimal);
	return SDL_roundf(v * rounder) / rounder;
}

int main() {
	const auto DECIMAL_PLACES = 4;
	
	const SDL_FPoint answer {3.093023, 1.162791};
	
	SDL_FPoint p1 {1, 2};
	SDL_FPoint p2 {6, 0};
	SDL_FPoint p3 {3, 1};
	SDL_FPoint p4 {7, 8};
    SDL_FPoint intersection {0,0};
	
	Game::getIntersection(p1, p2, p3, p4, intersection);
	
	if (
		round(intersection.x, DECIMAL_PLACES) == round(answer.x, DECIMAL_PLACES) &&
		round(intersection.y, DECIMAL_PLACES) == round(answer.y, DECIMAL_PLACES)
	) return 0;
	
	return 1;
}