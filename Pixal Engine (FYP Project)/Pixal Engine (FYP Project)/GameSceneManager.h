#pragma once
#include "SDL.h"
#include "Commons.h"
#include "GameScene.h"

class GameScene;

class GameSceneManager
{
private:
	SDL_Renderer* m_renderer = nullptr;
	GameScene* m_current_screen = nullptr;
	//SCREENS m_currentScreenType = SCREEN_MENU;
	static GameSceneManager* m_instance;

public:
	GameSceneManager(SDL_Renderer* renderer);
	~GameSceneManager();

	static GameSceneManager* Instance(SDL_Renderer* renderer);

	void Render();
	void Update(float deltaTime, SDL_Event e);

	//void ChangeScreen(SCREENS new_screen);
	bool GetQuit();
};


