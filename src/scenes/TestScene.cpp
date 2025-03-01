#include "scenes/TestScene.h"
#include "SDL3/SDL.h"

void TestScene::Render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 250, 250, 210, 255);
  SDL_RenderClear(renderer);
}

void TestScene::Update(double deltaTime) {}

void TestScene::HandleEvent(SDL_Event& event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    SDL_Log("Hejka testscena");
  }
}