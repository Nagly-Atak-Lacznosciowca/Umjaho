#include "game/entities/Player.h"
#include "game/Game.h"

Player::Player(const double x, const double y, const double width, const double length, const double angle, const double zIndex, SDL_Texture* texture) : Car(
        x, y, 0, -1, width, length, angle, zIndex, texture) {}

// Sets player's texture based on color set in Game
// TODO: Add textures based on turn direction
void Player::SetTexture() {
  std::string textureName = "car-" + Game::playerColor + "-regular.png";
  texture = Game::textures.at(textureName);
}