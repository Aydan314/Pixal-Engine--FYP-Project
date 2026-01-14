#include "Hitbox2D.h"

Hitbox2D::Hitbox2D()
{
	owner = nullptr;
	m_renderer = nullptr;
	size = Vector2D();
}

Hitbox2D::Hitbox2D(Transform* _owner, Vector2D _size, Vector2D _position, SDL_Renderer* renderer)
{
	owner = _owner;
	size = _size;
	m_position = _position;
	m_renderer = renderer;
}

bool Hitbox2D::ContainsPoint(Vector2D point)
{
	if (owner != nullptr) 
	{
		if (point.x > (owner->position.x + m_position.x) && point.x < (size.x + owner->position.x + m_position.x)) 
		{
			if (point.y > (owner->position.y + m_position.y) && point.y < (size.y + owner->position.y + m_position.y)) 
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

		rect.x = (owner->position.x + m_position.x) * owner->scale.x;
		rect.y = (owner->position.y + m_position.y) * owner->scale.y;
		rect.w = size.x * owner->scale.x;
		rect.h = size.y * owner->scale.y;

		SDL_SetRenderDrawColor(m_renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);

		SDL_RenderDrawRect(m_renderer, &rect);
	}
}

void Hitbox2D::SetColour(SDL_Color colour)
{
	m_colour = colour;
}

void Hitbox2D::SetPosition(Vector2D position)
{
	m_position = position;
}

Vector2D Hitbox2D::GetPosition()
{
	return m_position;
}
