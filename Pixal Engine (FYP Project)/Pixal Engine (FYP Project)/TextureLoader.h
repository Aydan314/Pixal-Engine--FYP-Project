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
	SDL_Renderer* m_renderer = nullptr;
	void loadSurfaces();

	TextureLoader(SDL_Renderer* renderer);

	static TextureLoader* m_instance;

public:
	~TextureLoader();

	TextureData GetTexture(std::string name);

	static TextureLoader* Instance(SDL_Renderer* renderer);
};