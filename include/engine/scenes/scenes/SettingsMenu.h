#ifndef UMJAHO_SETTINGSMENU_H
#define UMJAHO_SETTINGSMENU_H

#include "Menu.h"
#include "engine/scenes/Text.h"

class SettingsMenu: public Menu{
	public:
		Text* currentCarColorLabel = nullptr;
		
		SettingsMenu();
		~SettingsMenu() override;
	
		void logic() override;
		void handleEvent(SDL_Event *event) override;
};

#endif //UMJAHO_SETTINGSMENU_H
