#include "Hitbox2D.h"

Hitbox2D::Hitbox2D()
{
	position = nullptr;
	m_renderer = nullptr;
	size = Vector2D();
}

Hitbox2D::Hitbox2D(Vector2D* _position, Vector2D _size, SDL_Renderer* renderer)
{
	position = _position;
	size = _size;
	m_renderer = renderer;
}

bool Hitbox2D::ContainsPoint(Vector2D point)
{
	if (position != nullptr) 
	{
		if (point.x > position->x && point.x < size.x + position->x) 
		{
			if (point.y > position->y && point.y < size.y + position->y) 
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

void Hitbox2D::Draw()
{
	if (m_renderer) 
	{
		SDL_Rect rect;

		rect.x = position->x;
		rect.y = position->y;
		rect.w = size.x;
		rect.h = size.y;

		SDL_SetRenderDrawColor(m_renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);

		SDL_RenderDrawRect(m_renderer, &rect);
	}
}

void Hitbox2D::SetColour(SDL_Color colour)
{
	m_colour = colour;
}
