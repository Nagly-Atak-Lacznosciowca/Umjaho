#ifndef UMJAHO_PAUSEMENU_H
#define UMJAHO_PAUSEMENU_H

#include "Menu.h"

class PauseMenu: public Menu {
	public:
		PauseMenu();
		~PauseMenu() = default;
		
		void logic() override;
		void handleEvent(SDL_Event *event) override;
};

#endif //UMJAHO_PAUSEMENU_H
