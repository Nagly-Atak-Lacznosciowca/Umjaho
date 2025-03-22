#ifndef UMJAHO_SCENE_H
#define UMJAHO_SCENE_H

#include <vector>
#include "SceneElement.h"
#include "engine/Renderer.h"

// should only be used as an abstract class that itself doesn't do anything skibidi
class Scene {
public:
    Scene();
    std::vector<SceneElement*> contents;
    // string name;
    void render(Renderer& renderer);
    virtual void logic();
    virtual void handleEvent(SDL_Event* event);
};

#endif //UMJAHO_SCENE_H
