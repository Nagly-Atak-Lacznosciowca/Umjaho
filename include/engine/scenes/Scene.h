#ifndef UMJAHO_SCENE_H
#define UMJAHO_SCENE_H

#include <vector>
#include "SceneElement.h"
#include "engine/Renderer.h"

// should only be used as an abstract class that itself doesn't do anything skibidi
class Scene {
	public:
		SDL_Texture* background = nullptr;
		std::vector<SceneElement*> contents;
		
	    Scene() = default;
	    virtual ~Scene();
		
	    virtual void logic() = 0;
	    virtual void handleEvent(SDL_Event* event) = 0;
		
	    void deleteElement(SceneElement* element);
	    void render();
};

#endif //UMJAHO_SCENE_H
