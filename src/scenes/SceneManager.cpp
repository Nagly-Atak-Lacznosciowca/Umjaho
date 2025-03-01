#include "scenes/SceneManager.h"

SceneManager::SceneManager() : currentScene(nullptr) {}

SceneManager::~SceneManager() {
  if (currentScene) {
    delete currentScene;
    currentScene = nullptr;
  }
}

void SceneManager::Render(SDL_Renderer* renderer) {
  if (currentScene) {
    currentScene->Render(renderer);
  }
}

void SceneManager::Update(double deltaTime) {
  if (currentScene) {
    currentScene->Update(deltaTime);
  }
}

void SceneManager::HandleEvent(SDL_Event& event) {
  if (currentScene) {
    currentScene->HandleEvent(event);
  }
}

void SceneManager::ChangeScene(Scene* newScene) {
  if (currentScene) {
    delete currentScene;
  }
  currentScene = newScene;
}