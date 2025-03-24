
#include "game/Game.h"
#include "engine/scenes/scenes/Level1.h"
#include "engine/scenes/scenes/Menu.h"
#include <filesystem>

std::map<std::string, SDL_Texture*> Game::textures = {};

Game::Game(): lastTick(0), deltaTime(0), renderer(Renderer()), sceneManager(SceneManager()) {

}

void Game::init() {
	for (const auto &entry: std::filesystem::directory_iterator("../assets/textures/")) {
		SDL_Surface *surface = SDL_LoadBMP(entry.path().string().c_str());
		if (surface == nullptr) {
			SDL_Log("Błąd bmp %s", SDL_GetError());
		}
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.SDLRenderer, surface);
		if (texture == nullptr) {
			SDL_Log("Błąd tekstura %s", SDL_GetError());
		}
		textures.insert({entry.path().filename().string(), texture});
		SDL_Log("Loading %ls", entry.path().c_str());
	}

	auto level = new Level1();
    auto menu = new Menu([this]{ this->sceneManager.popScene(); });
	sceneManager.addScene(menu);
	sceneManager.addScene(level);
}

bool Game::checkSpeedControls()
{
	return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S];
}

bool Game::checkTurnControls()
{
	return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A]
	|| SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D];
}


bool getIntersection(const SDL_FPoint p1, const SDL_FPoint p2,
					 const SDL_FPoint p3, const SDL_FPoint p4, SDL_FPoint &intersection) {
	const float x1 = p1.x, y1 = p1.y;
	const float x2 = p2.x, y2 = p2.y;
	const float x3 = p3.x, y3 = p3.y;
	const float x4 = p4.x, y4 = p4.y;

	const float denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (denom == 0) return false;

	const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
	const float u = -(((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom);

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
		intersection.x = x1 + t * (x2 - x1);
		intersection.y = y1 + t * (y2 - y1);
		return true;
	}

	return false;
}


SDL_FPoint* Game::checkElementCollision(SceneElement *elem1, SceneElement *elem2) {
	auto elem1Points = elem1->getPoints();
	auto elem2Points = elem2->getPoints();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			SDL_FPoint intersection;
			if (getIntersection(elem1Points[i], elem1Points[(i + 1) % 4],
								elem2Points[j], elem2Points[(j + 1) % 4], intersection)) {
				delete[] elem1Points;
				delete[] elem2Points;
				return new SDL_FPoint{intersection.x, intersection.y};
								}
		}
	}

	delete[] elem1Points;
	delete[] elem2Points;
	return nullptr;
}


Game::~Game() {
    for (const auto &item: Game::textures) {
        delete item.second;
    }
}

