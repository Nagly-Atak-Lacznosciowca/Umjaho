#ifndef UMJAHO_MENU_H
#define UMJAHO_MENU_H

#include "engine/scenes/Scene.h"

class Menu : public Scene {
	public:
	    Menu();
		~Menu() = default;
		
	    void logic() override;
	    void handleEvent(SDL_Event *event) override;
	private:
};

#endif //UMJAHO_MENU_H
