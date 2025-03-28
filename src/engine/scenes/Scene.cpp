#include "engine/scenes/Scene.h"
#include <stdexcept>

void Scene::render(Renderer& renderer) {
    SDL_RenderTexture(renderer.SDLRenderer, this->background, nullptr, nullptr);
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

Scene::~Scene() {
    for (const auto &item: this->contents) {
        delete item;
    }
}

void Scene::deleteElement(SceneElement *element){
    for(int i = 0; i<contents.size(); i++){
        if(contents.at(i) == element){
            contents.erase(contents.begin()+i);
        }
    }
}
