#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "Commons.h"
#include "TextureLoader.h"

#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

class Texture2D
{
private:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;

	int m_width = 0;
	int m_height = 0;

	int m_columns = 0;
	int m_rows = 0;

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(std::string path, int columns = 1, int rows = 1);
	void Free();
	void Render(Vector2D new_position, SDL_RendererFlip flip, int columnNum = 0, int rowNum = 0, double angle = 0.0, Vector2D scale = Vector2D(1.f,1.f));

	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
};

#endif // _TEXTURE2D_H



