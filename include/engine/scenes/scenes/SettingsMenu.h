#ifndef UMJAHO_SETTINGSMENU_H
#define UMJAHO_SETTINGSMENU_H
#include "engine/scenes/Scene.h"

class SettingsMenu: public Scene{
public:
    SettingsMenu();
    ~SettingsMenu() = default;

    void logic() override;
    void handleEvent(SDL_Event *event) override;
};

#endif //UMJAHO_SETTINGSMENU_H
