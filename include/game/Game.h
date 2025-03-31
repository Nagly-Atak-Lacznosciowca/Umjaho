#ifndef UMJAHO_GAME_H
#define UMJAHO_GAME_H

#include <queue>
#include <functional>
#include <map>
#include <string>

#include "engine/Renderer.h"
#include "entities/Car.h"
#include "engine/scenes/SceneManager.h"
#include "engine/sounds/SoundManager.h"
#include "entities/surfaces/Surface.h"
#include "SDL3_ttf/SDL_ttf.h"

class Game {
	public:
		// both values in ns
		unsigned long long lastTick = 0;
		unsigned long long deltaTime = 0;

		static Renderer renderer;
		static std::map<std::string, SDL_Texture*> textures;
		static SceneManager sceneManager;
		static SoundManager soundManager;
		static SDL_AudioDeviceID audioDeviceID;
		static TTF_Font* font;
		static std::string playerColor;
		static std::vector<std::pair<Uint64, Uint64>> playerTimes[3];
		static bool showFPS;

		Game();
		~Game();
		
		void init();
		
		static void loadFont();
		static void loadTextures();
		static void loadSounds();
		
		static bool checkSpeedControls();
		static bool checkTurnControls();
		static bool getIntersection(SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3, SDL_FPoint p4, SDL_FPoint &intersection);
		static SDL_FPoint* checkElementCollision(SceneElement *elem1, SceneElement *elem2);
		static bool checkSurfaceIntersection(Car *car, Surface *surface);
};

#endif //UMJAHO_GAME_H
