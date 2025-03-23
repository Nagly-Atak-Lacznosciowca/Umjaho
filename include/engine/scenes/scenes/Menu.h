#ifndef UMJAHO_MENU_H
#define UMJAHO_MENU_H

#include "engine/scenes/Scene.h"
#include <functional>

class Menu : public Scene {
public:
    explicit Menu(const std::function<void()>& playButtonAction);
    void logic() override;
    void handleEvent(SDL_Event *event) override;

};

#endif //UMJAHO_MENU_H
