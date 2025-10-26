#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

GameScene::~GameScene()
{
	m_renderer = nullptr;
}

void GameScene::Render()
{
}

void GameScene::Update(float deltaTime, SDL_Event e)
{
}

bool GameScene::GetQuit()
{
	return quit;
}
