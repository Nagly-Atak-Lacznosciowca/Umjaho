#ifndef UMJAHO_MENU_H
#define UMJAHO_MENU_H

#include "engine/scenes/Scene.h"
#include "game/Game.h"
#include <functional>

class Menu : public Scene {
public:
    explicit Menu(SceneManager* sceneManager);
    void logic() override;
    void handleEvent(SDL_Event *event) override;
	void startLevel();
private:
	SceneManager* sceneManager;
};

#endif //UMJAHO_MENU_H
