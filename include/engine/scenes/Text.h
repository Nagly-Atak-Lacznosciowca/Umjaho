#ifndef UMJAHO_TEXT_H
#define UMJAHO_TEXT_H
#include "engine/scenes/SceneElement.h"
#include "string"

class Text: public SceneElement{
	public:
		std::string content;
		SDL_Color color;
		
		Text(double x, double y, double width = 50, double height = 50, double angle = 0, double zIndex = 0, const std::string& text = "", const SDL_Color color = SDL_Color { 255, 255, 255 });
		~Text() override;
		
		void setContent(const std::string& text);
		void setColor(const SDL_Color color);
		
	private:
		bool dynamicWidth;
		bool dynamicHeight;
		
		void updateSurface();
};

#endif //UMJAHO_TEXT_H
