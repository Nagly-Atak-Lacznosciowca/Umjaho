#ifndef UMJAHO_SCENEMANAGER_H
#define UMJAHO_SCENEMANAGER_H

#include <queue>

#include "Scene.h"

class SceneManager {
public:
    SceneManager();
    void addScene(Scene *scene);
    void popScene();
    Scene* currentScene();
private:
    std::queue<Scene*> scenes;
};

#endif //UMJAHO_SCENEMANAGER_H
