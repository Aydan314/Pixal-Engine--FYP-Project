#pragma once
#include "Vector2D.h"
#include "SDL.h"

class Hitbox2D
{
private:
	SDL_Renderer* m_renderer;
	SDL_Color m_colour {200,0,0,255};

public :
	Vector2D* position;
	Vector2D size;

	Hitbox2D();
	Hitbox2D(Vector2D* _position, Vector2D _size, SDL_Renderer* renderer = nullptr);

	bool ContainsPoint(Vector2D point);

	void Draw();
	void SetColour(SDL_Color colour);

};

