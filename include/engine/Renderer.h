#ifndef UMJAHO_RENDERER_H
#define UMJAHO_RENDERER_H

#include "SDL3/SDL.h"
#include "engine/scenes/SceneManager.h"
#include "array"

class Renderer {
public:
    Renderer();
    ~Renderer();
    void Init(int width, int height);
    void Clear();
    void Present();

    SDL_Renderer* SDLRenderer;
    SDL_Window* SDLWindow;
    SceneManager* sceneManager;
private:

};

#endif //UMJAHO_RENDERER_H
