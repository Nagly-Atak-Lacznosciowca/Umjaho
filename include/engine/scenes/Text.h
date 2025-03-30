#ifndef UMJAHO_TEXT_H
#define UMJAHO_TEXT_H
#include "engine/scenes/SceneElement.h"
#include "string"

class Text: public SceneElement{
	public:
		Text(double x, double y, double width = 50, double height = 50, double angle = 0, double zIndex = 0, const std::string& text = "", const SDL_Color color = SDL_Color { 255, 255, 255 });
			~Text() override;
		std::string content;
		SDL_Color color;

		void setContent(const std::string& text);
		void setColor(const SDL_Color color);
	
	private:
		void updateText();
			
};

#endif //UMJAHO_TEXT_H
