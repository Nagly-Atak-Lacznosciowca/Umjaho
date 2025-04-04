#ifndef UMJAHO_LEVELBUTTON_H
#define UMJAHO_LEVELBUTTON_H

#include "Button.h"
#include "engine/scenes/scenes/Level.h"

template <typename LevelClass>
class LevelButton: public Button{
public:
    LevelButton(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture, const std::string &text, SDL_Texture* image, int levelId);
	
    SDL_Texture* image;
	int levelId;
	Uint64 *bestTime;
	Text *bestTimeText;
	bool left;

    void click(float x, float y) override;
    void render() override;
};

#include "engine/scenes/controls/LevelButton.tpp"

#endif //UMJAHO_LEVELBUTTON_H
