#ifndef UMJAHO_TEST_SCENE_H
#define UMJAHO_TEST_SCENE_H

#include "SDL3/SDL.h"
#include "scenes/Scene.h"

class TestScene : public Scene {
public:
  void Render(SDL_Renderer* renderer) override;
  void Update(double deltaTime) override;
  void HandleEvent(SDL_Event& event) override;
};

#endif