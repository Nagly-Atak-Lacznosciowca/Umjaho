#include "engine/scenes/SceneManager.h"

SceneManager::SceneManager() {
    scenes = std::stack<Scene*>();
};

void SceneManager::pushScene(Scene *scene) {;
    scenes.push(scene);
}

void SceneManager::popScene() {
	auto top = scenes.top();
    scenes.pop();
    delete top;
}

Scene* SceneManager::currentScene() {
    return scenes.top();
}