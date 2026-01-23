#pragma once
#include "SDL.h"
#include "iostream"
#include "GameObject.h"

class GameScene
{
protected:
	SDL_Renderer* m_renderer = nullptr;
	bool quit = false;
	std::vector<GameObject*> m_contents;
private:

public:
	GameScene(SDL_Renderer* renderer);
	~GameScene();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void Add(GameObject* object);
	void Clear();

	SDL_Renderer* GetRenderer();
	bool GetQuit();
};

