#include <algorithm>
#include "engine/scenes/NitroBattery.h"
#include "game/Game.h"

NitroBattery::NitroBattery(double x, double y, double width, double height, double angle, double zIndex, int state) : SceneElement(x, y, width, height, angle, zIndex, Game::textures.at("nitro" + std::to_string(state) + ".png"))
{}

void NitroBattery::setState(int value)
{
	this->state = std::min(value, Car::NEEDED_CHARGES);
	this->texture = Game::textures.at("nitro" + std::to_string(state) + ".png");
}