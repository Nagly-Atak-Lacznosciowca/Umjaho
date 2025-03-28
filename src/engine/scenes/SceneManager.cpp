#include "engine/scenes/SceneManager.h"

SceneManager::SceneManager() {
    scenes = std::stack<Scene*>();
};

void SceneManager::pushScene(Scene *scene) {;
    scenes.push(scene);
}

void SceneManager::popScene() {
	// delete scenes.top();
    scenes.pop();
}

Scene* SceneManager::currentScene() {
    return scenes.top();
}