#pragma once

#include "SDL3/SDL.h"

#ifndef UMJAHO_RENDERER_H
#define UMJAHO_RENDERER_H

class Renderer {
public:
    Renderer();
    ~Renderer();
    void Init(int width, int height);
    void Clear();
    void Present();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif //UMJAHO_RENDERER_H
