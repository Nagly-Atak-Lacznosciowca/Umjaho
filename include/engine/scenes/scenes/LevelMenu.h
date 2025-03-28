#ifndef UMJAHO_LEVELMENU_H
#define UMJAHO_LEVELMENU_H

#include "engine/scenes/Scene.h"

class LevelMenu: public Scene {
	public:
		LevelMenu();
		~LevelMenu() = default;
		
		void logic() override;
		void handleEvent(SDL_Event *event) override;
};

#endif //UMJAHO_LEVELMENU_H
