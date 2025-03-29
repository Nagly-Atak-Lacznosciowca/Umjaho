#ifndef UMJAHO_MAINMENU_H
#define UMJAHO_MAINMENU_H

#include "Menu.h"

class MainMenu : public Menu {
	public:
	    MainMenu();
		~MainMenu() = default;
		
	    void logic() override;
	    void handleEvent(SDL_Event *event) override;
		
	private:
		static void goToLevelMenu();
		static void goToSettingsMenu();
		static void goToCredits();
		static void exitGame();
};

#endif //UMJAHO_MAINMENU_H
