#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f; y = 0.0f;
}

Vector2D::Vector2D(float init_x, float init_y)
{
	x = init_x; y = init_y;
}

Vector2D Vector2D::operator+(const Vector2D& Other)
{
	return Vector2D(x + Other.x, y + Other.y);
}

Vector2D Vector2D::operator-(const Vector2D& Other)
{
	return Vector2D(x - Other.x, y - Other.y);
}

Vector2D Vector2D::operator*(const Vector2D& Other)
{
	return Vector2D(x * Other.x, y * Other.y);
}

Vector2D Vector2D::operator/(const Vector2D& Other)
{
	return Vector2D(x / Other.x, y / Other.y);
}
