#ifndef UMJAHO_SCENEMANAGER_H
#define UMJAHO_SCENEMANAGER_H

#include <stack>

#include "Scene.h"

class SceneManager {
	public:
	    SceneManager();
	    void pushScene(Scene *scene);
	    void popScene();
	    Scene* currentScene();
	
	private:
	    std::stack<Scene*> scenes;
};

#endif //UMJAHO_SCENEMANAGER_H
