#ifndef UMJAHO_LEVELBUTTON_H
#define UMJAHO_LEVELBUTTON_H

#include "Button.h"
#include "engine/scenes/scenes/Level.h"

class LevelButton: public Button{
public:
    LevelButton(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture,
                Level *level, const std::string &text, SDL_Texture* image);

    Level* level;
    SDL_Texture* image;

    void click(float x, float y) const override;
    void render() override;
};

#endif //UMJAHO_LEVELBUTTON_H
