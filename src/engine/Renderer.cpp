#include "engine/Renderer.h"
#include "engine/scenes/SceneManager.h"

Renderer::Renderer() : SDLRenderer(nullptr), SDLWindow(nullptr), sceneManager(new SceneManager()) {}

Renderer::~Renderer() {
    SDL_DestroyRenderer(SDLRenderer);
    SDL_DestroyWindow(SDLWindow);
}

void Renderer::Init(int width, int height) {
    
}

void Renderer::Clear() {
    SDL_RenderClear(SDLRenderer);
}

void Renderer::Present() {
    SDL_RenderPresent(SDLRenderer);
}