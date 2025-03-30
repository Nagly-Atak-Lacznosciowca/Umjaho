#include <stdexcept>
#include "game/Game.h"
#include "game/entities/surfaces/Surface.h"

Surface::Surface(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture* texture) : SceneElement(x, y, width, height, angle, zIndex, texture) {}

void Surface::collide(SceneElement* element) {
    if (auto car = dynamic_cast<Car*>(element)) {
        Game::sceneManager.currentScene()->deleteElement(this);
        action(car);
    }
}

void Surface::action(Car* car) {
    throw std::runtime_error("Not implemented");
}