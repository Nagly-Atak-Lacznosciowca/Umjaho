#include "game/Game.h"

int main() {
	std::string textures[] = {
		"button.png",
		"car-blue-regular.png",
		"car-green-regular.png",
		"car-orange-regular.png",
		"car-purple-regular.png",
		"car-red-regular.png",
		"car-yellow-regular.png",
		"cone.png",
		"curb.png",
		"dirt.png",
		"gate-closed.png",
		"gate-open.png",
		"ice.png",
		"level-button.png",
		"level-menu.png",
		"oil.png",
		"pause-menu.png",
		"speedbump.png",
		"title-no-buttons.png",
		"title.png",
		"track1.png",
		"track2.png",
		"track3.png",
		"water.png"
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