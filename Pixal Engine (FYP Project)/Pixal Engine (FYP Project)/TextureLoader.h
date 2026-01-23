#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Commons.h"
#include <iostream>
#include <vector>

class TextureLoader
{
private:
	std::vector<TextureData> m_loadedSurfaces = {};
	std::vector<TextureData> m_gameLoadedSurfaces = {};

	SDL_Renderer* m_renderer = nullptr;
	SDL_Renderer* m_gameRenderer = nullptr;
	void loadSurfaces();
	void loadGameSurfaces();

	TextureLoader(SDL_Renderer* renderer);

	static TextureLoader* m_instance;

public:
	~TextureLoader();

	TextureData GetTexture(std::string name);
	TextureData GetGameTexture(std::string name);
	SDL_Renderer* GetRenderer();

	static TextureLoader* Instance(SDL_Renderer* renderer);
	void SetGameRenderer(SDL_Renderer* renderer);
};