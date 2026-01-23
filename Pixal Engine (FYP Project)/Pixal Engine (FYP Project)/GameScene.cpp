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
	for (GameObject* object : m_contents) 
	{
		object->Render();
	}
}

void GameScene::Update(float deltaTime, SDL_Event e)
{
	for (GameObject* object : m_contents) 
	{
		object->Update(deltaTime, e);
	}
}

void GameScene::Add(GameObject* object)
{
	m_contents.push_back(object);
}

void GameScene::Clear()
{
	for (GameObject* object : m_contents) 
	{
		object->Delete();
	}
	m_contents.clear();
}

SDL_Renderer* GameScene::GetRenderer()
{
	return m_renderer;
}

bool GameScene::GetQuit()
{
	return quit;
}
