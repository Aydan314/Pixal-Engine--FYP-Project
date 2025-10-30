#pragma once
#include "Vector2D.h"
#include "SDL.h"
#include "Commons.h"

class Hitbox2D
{
private:
	SDL_Renderer* m_renderer;
	SDL_Color m_colour {200,0,0,255};

public :
	Transform* owner;
	Vector2D size;

	Hitbox2D();
	Hitbox2D(Transform* _owner, Vector2D _size, SDL_Renderer* renderer = nullptr);

	bool ContainsPoint(Vector2D point);

	void Draw();
	void SetColour(SDL_Color colour);

};

