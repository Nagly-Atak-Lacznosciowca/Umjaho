
#include "game/Game.h"
#include "engine/scenes/scenes/Level1.h"
#include "engine/scenes/scenes/Menu.h"
#include <filesystem>

std::map<std::string, SDL_Texture*> Game::textures;
SoundManager Game::soundManager;

Game::Game(): lastTick(0), deltaTime(0), renderer(Renderer()), sceneManager(SceneManager()) {}

void Game::init() {
	for (const auto &entry: std::filesystem::directory_iterator("../assets/sounds/")) {
		auto *audioSpec = new SDL_AudioSpec;
		auto **audioBuffer = new Uint8*;
		auto *audioLength = new Uint32;
		
		if (!SDL_LoadWAV(entry.path().string().c_str(), audioSpec, audioBuffer, audioLength)) {
			SDL_Log("Couldn't load WAV file: %s", SDL_GetError());
		}
		
		auto *audioStream = SDL_CreateAudioStream(audioSpec, nullptr);
		
		Game::soundManager.registerSound(entry.path().filename().string(), new Sound(
			audioStream,
			*audioBuffer,
			(int)*audioLength
		));
		
		SDL_Log("Loading %ls", entry.path().c_str());
	}
	
	auto *countPtr = new int();
	
	SDL_AudioDeviceID *audioPlaybackDevices = SDL_GetAudioPlaybackDevices(countPtr);
	
	int count = *countPtr;
	
	delete countPtr;
	
	if (audioPlaybackDevices == nullptr)
	{
		SDL_Log("Couldn't get playback devices: %s", SDL_GetError());
	}
	
	// count is 0 on error
	for (int i = 0; i < count; i++)
	{
		// SDL_AudioDeviceID currentDeviceID = audioPlaybackDevices[i]; // and cannot be null
		//
		// SDL_Log("Device %d name %s", currentDeviceID, SDL_GetAudioDeviceName(currentDeviceID));
		//
		// auto *currentSpec = new SDL_AudioSpec;
		//
		// if (!SDL_GetAudioDeviceFormat(currentDeviceID, currentSpec, nullptr)) {
		// 	SDL_Log("Couldn't get audio device format for %d: %s", currentDeviceID, SDL_GetError());
		// }
		//
		// auto *audioStream = SDL_CreateAudioStream(sounds[0].audioSpec, currentSpec);
		//
		// if (audioStream == nullptr) {
		// 	SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
		// }
		//
		// // if (!SDL_PutAudioStreamData(audioStream, sounds[0].audioBuffer, sounds[0].audioLength)) {
		// // 	SDL_Log("Couldn't put audio data to stream: %s", SDL_GetError());
		// // }
		//
		// SDL_ResumeAudioStreamDevice(audioStream);
	}
	
	// SDL_AudioDeviceID currentDeviceID = 31; // and cannot be null
	//
	// SDL_Log("Device %d name %s", currentDeviceID, SDL_GetAudioDeviceName(currentDeviceID));
	//
	// auto *currentSpec = new SDL_AudioSpec;
	//
	// if (!SDL_GetAudioDeviceFormat(currentDeviceID, currentSpec, nullptr)) {
	// 	SDL_Log("Couldn't get audio device format for %d: %s", currentDeviceID, SDL_GetError());
	// }
	//
	// if (SDL_OpenAudioDevice(currentDeviceID, currentSpec) == 0) {
	// 	SDL_Log("Couldn't open audio device: %s", SDL_GetError());
	// }
	//
	// auto *audioStream = SDL_CreateAudioStream(sounds[0].audioSpec, currentSpec);
	//
	// if (audioStream == nullptr) {
	// 	SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
	// }
	//
	// if (!SDL_PutAudioStreamData(audioStream, sounds[0].audioBuffer, sounds[0].audioLength)) {
	// 	SDL_Log("Couldn't put audio data to stream: %s", SDL_GetError());
	// }
	//
	// SDL_ResumeAudioStreamDevice(audioStream);

	SDL_free(audioPlaybackDevices);
	
	// SDL_AudioSpec *defaultPlaybackSpec;
	// SDL_AudioSpec *defaultRecordingSpec;
	//
	// SDL_GetAudioDeviceFormat(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, defaultPlaybackSpec, nullptr);
	// SDL_GetAudioDeviceFormat(SDL_AUDIO_DEVICE_DEFAULT_RECORDING, defaultRecordingSpec, nullptr);
	//
	// this->sfxStream = SDL_CreateAudioStream(
	// 	defaultRecordingSpec,
	// 	defaultPlaybackSpec
	// );
	
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
	
    auto menu = new Menu(&sceneManager);
	sceneManager.pushScene(menu);
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

SDL_FPoint* Game::getIntersection(const SDL_FPoint p1, const SDL_FPoint p2, const SDL_FPoint p3, const SDL_FPoint p4)
{
	const float x1 = p1.x;
	const float y1 = p1.y;
	const float x2 = p2.x;
	const float y2 = p2.y;

	const float x3 = p3.x;
	const float y3 = p3.y;
	const float x4 = p4.x;
	const float y4 = p4.y;

	// math from https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Formulas
	const float denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	if (denom == 0) {
		return nullptr;
	}

	const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
	const float u = -1 * (((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom);

	if (!((t >= 0 && t <= 1) && (u >= 0 && u <= 1)))
		return nullptr;

	const float intersectionX = x1 + t * (x2 - x1);
	const float intersectionY = y1 + t * (y2 - y1);

	return new SDL_FPoint {intersectionX, intersectionY};
}

// TO DO support rotated cars
SDL_FPoint* Game::checkElementCollision(SceneElement *elem1, SceneElement *elem2)
{
	auto elem1Points = elem1->getPoints();
	auto elem2Points = elem2->getPoints();
	
	SDL_FPoint elem1Lines[][4] = {
		{
			elem1Points[0],
			elem1Points[1]
		},
		{
			elem1Points[1],
			elem1Points[2]
		},
		{
			elem1Points[2],
			elem1Points[3]
		},
		{
			elem1Points[3],
			elem1Points[4]
		},
	};
	
	SDL_FPoint elem2Lines[][4] = {
		{
			elem2Points[0],
			elem2Points[1]
		},
		{
			elem2Points[1],
			elem2Points[2]
		},
		{
			elem2Points[2],
			elem2Points[3]
		},
		{
			elem2Points[3],
			elem2Points[4]
		},
	};
	
	for (auto & elem1Line : elem1Lines)
		for (auto & elem2Line : elem2Lines) {
			SDL_FPoint* intersectionPoint = Game::getIntersection(elem1Line[0], elem1Line[1], elem2Line[0], elem2Line[1]);
			if (intersectionPoint != nullptr) {
				delete elem1Points;
				delete elem2Points;
				return intersectionPoint;
			}
		}

	delete elem1Points;
	delete elem2Points;
	
	return nullptr;
}

Game::~Game() {
    for (const auto &item: Game::textures) {
        delete item.second;
    }
}

