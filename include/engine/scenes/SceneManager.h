#ifndef UMJAHO_SCENEMANAGER_H
#define UMJAHO_SCENEMANAGER_H

#include "vector"
#include "Scene.h"

class SceneManager {
public:
    SceneManager();
private:
    std::vector<Scene> scenes;
};

#endif //UMJAHO_SCENEMANAGER_H
