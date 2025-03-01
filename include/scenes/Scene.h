#ifndef UMJAHO_SCENE_H
#define UMJAHO_SCENE_H

#include "SDL3/SDL.h"

class Scene {
public:
  virtual ~Scene() {};
  virtual void Render(SDL_Renderer* renderer) {};
  virtual void Update(double deltaTime) {};
  virtual void HandleEvent(SDL_Event& event) {};
};

#endif