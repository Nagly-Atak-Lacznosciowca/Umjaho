#include "engine/scenes/SceneManager.h"

SceneManager::SceneManager() {
    scenes = std::queue<Scene*>();
};

void SceneManager::addScene(Scene *scene) {
    scenes.push(scene);
}

void SceneManager::popScene() {
    scenes.pop();
}

Scene* SceneManager::currentScene() {
    return scenes.front();
}
