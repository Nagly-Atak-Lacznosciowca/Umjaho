#ifndef UMJAHO_RENDERER_H
#define UMJAHO_RENDERER_H

#include "SDL3/SDL.h"

class Renderer {
public:
    Renderer();
    ~Renderer();
    void Init(int width, int height);
    void Clear();
    void Present();

    SDL_Renderer* renderer;
    SDL_Window* window;
private:

};

#endif //UMJAHO_RENDERER_H
