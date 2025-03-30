#include "engine/scenes/controls/LevelButton.h"
#include "game/Game.h"
#include "game/Event.h"

LevelButton::LevelButton(double x, double y, double width, double height, double angle, double zIndex,
                         SDL_Texture *texture, Level *level, const std::string &text, SDL_Texture* image): Button(x,y,width,height,angle, zIndex,texture,
                                                                                                                  nullptr), level(level), image(image) {
    if(!text.empty()){
		const auto scale = height / 600;
        this->text = new Text(0, 0, 0, height/8, angle, zIndex, text);
	    this->text->x = x + width/2 - this->text->width/2;
	    this->text->y = y + 50 * scale - this->text->height/2;
    }
};

void LevelButton::click(float x, float y) const {
    if(level!= nullptr){
        SDL_PushEvent(new SDL_Event {
	        .user = {
	            .type = Event::CUSTOM_EVENT_PUSH_SCENE,
				.data1 = this->level
	        }
		});
    }
}

void LevelButton::render() {
    Button::render();
	
	const auto mapWidth = 390;
	const auto mapHeight = 390;
	
    SDL_RenderTexture(Game::renderer.SDLRenderer, this->image, nullptr,
                      new SDL_FRect{static_cast<float>(x + width/2 - (float)mapWidth/2), static_cast<float>(y + height/2 - (float)mapHeight/2), static_cast<float>(mapWidth), static_cast<float>(mapHeight)});
}

