
#include "game/Game.h"
#include "engine/scenes/scenes/Level1.h"
#include "engine/scenes/scenes/MainMenu.h"
#include "game/Event.h"
#include <filesystem>

Renderer Game::renderer;
std::map<std::string, SDL_Texture*> Game::textures;
SoundManager Game::soundManager;
SDL_AudioDeviceID Game::audioDeviceID;
SceneManager Game::sceneManager;
TTF_Font* Game::font;
std::string Game::playerColor = "blue";
bool Game::showFPS = false;

Game::Game(): lastTick(0), deltaTime(0) {}

void Game::init() {
	Game::loadFont();
	Game::loadTextures();
	Game::loadSounds();
	
	Game::soundManager.setVolume(0.5f);
	
	Game::sceneManager.pushScene(new MainMenu());
}

void Game::loadFont() {
	Game::font = TTF_OpenFont("../assets/fonts/Jersey25-Regular.ttf", 1000);
	
	if(Game::font == nullptr){
		SDL_Log("font fgdgd %s", SDL_GetError());
	}
}

void Game::loadTextures() {
	for (const auto &entry: std::filesystem::directory_iterator("../assets/textures/")) {
		SDL_Surface *surface = SDL_LoadBMP(entry.path().string().c_str());
		
		if (surface == nullptr) {
			SDL_Log("Couldn't load BMP: %s", SDL_GetError());
		}
		
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.SDLRenderer, surface);
		
		if (texture == nullptr) {
			SDL_Log("Couldn't create texture from surface: %s", SDL_GetError());
		}
		
		Game::textures.insert({entry.path().filename().string(), texture});

#ifdef DEBUG
		SDL_Log("Loaded texture: %ls", entry.path().c_str());
#endif
	}
	
	SDL_SetTextureScaleMode(textures.at("button.bmp"), SDL_SCALEMODE_NEAREST);
}

void Game::loadSounds() {
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

#ifdef DEBUG
		SDL_Log("Loaded sound: %ls", entry.path().c_str());
#endif
	}
}

bool Game::checkSpeedControls()
{
	const auto keyboardState = SDL_GetKeyboardState(nullptr);
	
	return keyboardState[SDL_SCANCODE_UP]
	|| keyboardState[SDL_SCANCODE_DOWN]
	|| keyboardState[SDL_SCANCODE_W]
	|| keyboardState[SDL_SCANCODE_S];
}

bool Game::checkTurnControls()
{
	const auto keyboardState = SDL_GetKeyboardState(nullptr);
	
	return keyboardState[SDL_SCANCODE_LEFT]
	|| keyboardState[SDL_SCANCODE_RIGHT]
	|| keyboardState[SDL_SCANCODE_A]
	|| keyboardState[SDL_SCANCODE_D];
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


bool Game::checkSurfaceIntersection(Car *car, Surface *surface) {
	auto carPoints = car->getPoints();
	auto surfacePoints = surface->getPoints();

	for (int i = 0; i < 4; i++) {
		SDL_FPoint carPoint = carPoints[i];
		int intersections = 0;

		for (int j = 0; j < 4; j++) {
			SDL_FPoint p1 = surfacePoints[j];
			SDL_FPoint p2 = surfacePoints[(j + 1) % 4];
			SDL_FPoint intersection;

			SDL_FPoint rayEnd = {carPoint.x + 10000.0f, carPoint.y};
			if (getIntersection(carPoint, rayEnd, p1, p2, intersection)) {
				intersections++;
			}
		}

		// Odd intersections mean the point is inside
		if (intersections % 2 == 1) {
			delete[] carPoints;
			delete[] surfacePoints;
			return true;
		}
	}

	delete[] carPoints;
	delete[] surfacePoints;
	return false;
}


Game::~Game() {
    for (const auto &item: Game::textures) {
        SDL_DestroyTexture(item.second);
    }
	
	
}

