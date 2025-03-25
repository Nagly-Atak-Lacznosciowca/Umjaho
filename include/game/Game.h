#ifndef UMJAHO_GAME_H
#define UMJAHO_GAME_H

#include <queue>
#include <functional>
#include <map>
#include <string>

#include "engine/Renderer.h"
#include "entity/Car.h"
#include "engine/scenes/SceneManager.h"
#include "engine/sounds/SoundManager.h"

class Game {
	public:
		// both values in ns
		unsigned long long lastTick = 0;
		unsigned long long deltaTime = 0;
		
		Renderer renderer;
		SceneManager sceneManager;
		
		static std::map<std::string, SDL_Texture*> textures;
		static SoundManager soundManager;
			
	    Game();
	    ~Game();
			
		void init();
	
	    static bool checkSpeedControls();
	    static bool checkTurnControls();
		static SDL_FPoint* checkElementCollision(SceneElement *elem1, SceneElement *elem2);
		
		static SDL_FPoint* getIntersection(SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3, SDL_FPoint p4);
		
	private:
};

#endif //UMJAHO_GAME_H
