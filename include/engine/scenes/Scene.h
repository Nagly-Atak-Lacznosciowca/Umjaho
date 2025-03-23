#ifndef UMJAHO_SCENE_H
#define UMJAHO_SCENE_H

#include <vector>
#include "SceneElement.h"
#include "engine/Renderer.h"

// should only be used as an abstract class that itself doesn't do anything skibidi
class Scene {
public:
    Scene() = default;
    ~Scene();
    std::vector<SceneElement*> contents;
    void render(Renderer& renderer);
    virtual void logic() = 0;
    virtual void handleEvent(SDL_Event* event) = 0;
    SDL_Texture* background = nullptr;

};

#endif //UMJAHO_SCENE_H
