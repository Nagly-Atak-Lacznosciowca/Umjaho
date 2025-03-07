#ifndef UMJAHO_SCENE_H
#define UMJAHO_SCENE_H

#include "vector"
#include "SceneElement.h"

// should only be used as an abstract class that itself doesn't do anything skibidi
class Scene {
public:
    std::vector<SceneElement> contents;
    // string name;
};

#endif //UMJAHO_SCENE_H
