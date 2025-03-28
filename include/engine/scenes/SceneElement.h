#ifndef UMJAHO_SCENEELEMENT_H
#define UMJAHO_SCENEELEMENT_H

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

#include "engine/Renderer.h"

class SceneElement {
public:
	double x, y;
	double width, height;
	double angle; // In radians
	
	int zIndex;
	int lastCollidedWall = 0;
	
	SDL_Texture* texture = nullptr;

	SceneElement(double x, double y, double width, double height, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
	
	SDL_FPoint *getPoints() const;
	
	void render() const;
    virtual ~SceneElement();
};

#endif //UMJAHO_SCENEELEMENT_H
