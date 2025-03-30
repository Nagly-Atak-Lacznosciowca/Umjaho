#include "engine/scenes/SceneManager.h"

SceneManager::SceneManager() {
    scenes = std::stack<Scene*>();
};

void SceneManager::pushScene(Scene *scene) {;
    scenes.push(scene);
}

void SceneManager::popScene() {
	if (this->scenes.size() <= 1)
		return;
	
	delete scenes.top();
    scenes.pop();
}

Scene* SceneManager::currentScene() {
    return scenes.top();
}