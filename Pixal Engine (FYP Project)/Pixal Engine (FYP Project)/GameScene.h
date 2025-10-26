#pragma once
#include "SDL.h"
#include "iostream"

class GameScene
{
protected:
	SDL_Renderer* m_renderer = nullptr;
	bool quit = false;
private:

public:
	GameScene(SDL_Renderer* renderer);
	~GameScene();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	bool GetQuit();
};

