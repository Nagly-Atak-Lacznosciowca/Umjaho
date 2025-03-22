#include "engine/scenes/Scene.h"
#include <stdexcept>

Scene::Scene() {
    this->contents = {};
}

void Scene::render(Renderer& renderer) {
    for (auto& sceneElement : this->contents) {
        sceneElement->render(renderer);
    }
}

void Scene::logic() {
    throw std::runtime_error("Not implemented");
}

void Scene::handleEvent(SDL_Event* event) {
    throw std::runtime_error("Not implemented");
}