#ifndef UMJAHO_SCENE_MANAGER_H
#define UMJAHO_SCENE_MANAGER_H

#include "SDL3/SDL.h"
#include "scenes/Scene.h"

class SceneManager {
public:
  SceneManager();
  ~SceneManager();
  void Render(SDL_Renderer* renderer);
  void Update(double deltaTime);
  void HandleEvent(SDL_Event& event);
  void ChangeScene(Scene* newScene);

private:
  Scene* currentScene;
};

#endif