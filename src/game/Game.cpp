
#include "game/Game.h"
#include "engine/scenes/scenes/Level1.h"
#include "engine/scenes/scenes/MainMenu.h"
#include <filesystem>

Renderer Game::renderer;
std::map<std::string, SDL_Texture*> Game::textures;
SoundManager Game::soundManager;
SDL_AudioDeviceID Game::audioDeviceID;
SceneManager Game::sceneManager;
TTF_Font* Game::font;

Game::Game(): lastTick(0), deltaTime(0) {}

void Game::init() {
    Game::font = TTF_OpenFont("../assets/fonts/Jersey25-Regular.ttf", 24);
    if(Game::font == nullptr){
        SDL_Log("font fgdgd %s", SDL_GetError());
    }

	Game::audioDeviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
	
	if (Game::audioDeviceID == 0)
		SDL_Log("Couldn't open default audio playback device: %s", SDL_GetError());
	
	for (const auto &entry: std::filesystem::directory_iterator("../assets/sounds/")) {
		auto *audioSpec = new SDL_AudioSpec;
		auto **audioBuffer = new Uint8*;
		auto *audioLength = new Uint32;
		
		if (!SDL_LoadWAV(entry.path().string().c_str(), audioSpec, audioBuffer, audioLength)) {
			SDL_Log("Couldn't load WAV file: %s", SDL_GetError());
		}
		
		Game::soundManager.registerSound(entry.path().filename().string(), new Sound(
			audioSpec,
			*audioBuffer,
			(int)*audioLength
		));
		
		SDL_Log("Loading %ls", entry.path().c_str());
	}
	
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
	
	// Game::soundManager.playSound("bus.wav");
	
    auto menu = new MainMenu();
	Game::sceneManager.pushScene(menu);
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


bool Game::getIntersection(const SDL_FPoint p1, const SDL_FPoint p2,
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

int getIntersectedLine(const SceneElement *obstacle, const SDL_FPoint *intersectionPoint) {
	auto obstaclePoints = obstacle->getPoints();
	for (int i = 0; i < 4; i++) {
		SDL_FPoint linePoint1 = obstaclePoints[i];
		SDL_FPoint linePoint2 = obstaclePoints[(i + 1) % 4];

		if ((intersectionPoint->x == linePoint1.x && intersectionPoint->y == linePoint1.y) || (intersectionPoint->x == linePoint2.x && intersectionPoint->y == linePoint2.y)) {
			return 0;
		}

		float dxc = intersectionPoint->x - linePoint1.x;
		float dyc = intersectionPoint->y - linePoint1.y;

		float dxl = linePoint2.x - linePoint1.x;
		float dyl = linePoint2.y - linePoint1.y;

		float crossProduct = dxc * dyl - dyc * dxl;
		if (crossProduct < 0.05 && crossProduct > -0.05) {		// Supposed to be 0, but float precision went on vacation, never came back
			return i+1;											// I hate floats so much
		}
	}
	return 0;
}


SDL_FPoint* Game::checkElementCollision(SceneElement *elem1, SceneElement *elem2) {
	auto elem1Points = elem1->getPoints();
	auto elem2Points = elem2->getPoints();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			SDL_FPoint intersection;
			if (Game::getIntersection(elem1Points[i], elem1Points[(i + 1) % 4],
								elem2Points[j], elem2Points[(j + 1) % 4],
								intersection)) {

				elem1->lastCollidedWall = getIntersectedLine(elem2, &intersection);

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

