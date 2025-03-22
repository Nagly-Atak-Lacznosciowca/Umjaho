#include <algorithm>

#include "game/Game.h"

Game::Game(): lastTick(0), deltaTime(0), renderer(Renderer()) {}

bool Game::checkSpeedControls()
{
	return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S];
}

bool Game::checkTurnControls()
{
	return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D];
}

SDL_FPoint *getIntersection(const SDL_FPoint p1, const SDL_FPoint p2, const SDL_FPoint p3, const SDL_FPoint p4)
{
	const float x1 = p1.x;
	const float y1 = p1.y;
	const float x2 = p2.x;
	const float y2 = p2.y;
	
	const float x3 = p3.x;
	const float y3 = p3.y;
	const float x4 = p4.x;
	const float y4 = p4.y;
	
	// math from https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Formulas
	const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
	const float u = -1 * ((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
	
	if (!((t >= 0 && t <= 1) && (u >= 0 && u <= 1)))
		return nullptr;
	
	const float intersectionX = x1 + t * (x2 - x1);
	const float intersectionY = y1 + t * (y2 - y1);
	
	return new SDL_FPoint {intersectionX, intersectionY};
}

// TO DO support rotated cars
bool Game::checkCarCollision(Car *car1, Car *car2)
{
	auto car1Points = car1->getPoints();
	auto car2Points = car2->getPoints();
	
	SDL_FPoint car1Lines[][4] = {
		{
			car1Points[0],
			car1Points[1]
		},
		{
			car1Points[1],
			car1Points[2]
		},
		{
			car1Points[2],
			car1Points[3]
		},
		{
			car1Points[3],
			car1Points[4]
		},
	};
	
	SDL_FPoint car2Lines[][4] = {
		{
			car2Points[0],
			car2Points[1]
		},
		{
			car2Points[1],
			car2Points[2]
		},
		{
			car2Points[2],
			car2Points[3]
		},
		{
			car2Points[3],
			car2Points[4]
		},
	};
	
	for (auto & car1Line : car1Lines)
		for (auto & car2Line : car2Lines)
			if (getIntersection(car1Line[0], car1Line[1], car2Line[0], car2Line[1]))
				return true;
	
	return false;
}