#ifndef UMJAHO_LEVELMENU_H
#define UMJAHO_LEVELMENU_H

#include "Menu.h"

class LevelMenu: public Menu {
	public:
		LevelMenu();
		~LevelMenu() = default;
		
		void logic() override;
		void handleEvent(SDL_Event *event) override;
};

#endif //UMJAHO_LEVELMENU_H
