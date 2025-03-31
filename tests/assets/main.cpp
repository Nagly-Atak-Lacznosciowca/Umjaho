#include "game/Game.h"

int main() {
	std::string textures[] = {
		"button.bmp",
		"car-blue-regular.bmp",
		"car-green-regular.bmp",
		"car-orange-regular.bmp",
		"car-purple-regular.bmp",
		"car-red-regular.bmp",
		"car-yellow-regular.bmp",
		"cone.bmp",
		"curb.bmp",
		"dirt.bmp",
		"gate-closed.bmp",
		"gate-open.bmp",
		"ice.bmp",
		"level-button.bmp",
		"level-menu.bmp",
		"oil.bmp",
		"pause-menu.bmp",
		"speedbump.bmp",
		"title-no-buttons.bmp",
		"title.bmp",
		"track1.bmp",
		"track2.bmp",
		"track3.bmp",
		"water.bmp"
	};
	
	const auto texturesCount = sizeof(textures) / sizeof(std::string);
	
	Game g;
	
	SDL_CreateWindowAndRenderer("", 0, 0, SDL_WINDOW_HIDDEN, &Game::renderer.SDLWindow, &Game::renderer.SDLRenderer);
	
	g.init();
	
	for (int i = 0; i < texturesCount; i++)
	{
		SDL_Log("%s", textures[i].c_str());
		
		if (Game::textures.at(textures[i]) == nullptr)
			return 1;
	}
	
	return 0;
}