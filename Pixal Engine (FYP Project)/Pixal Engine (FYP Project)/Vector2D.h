#pragma once
#include <iostream>
#include <string>

struct Vector2D
{

	float x;
	float y;

	Vector2D();
	Vector2D(float init_x, float init_y);
	float Magnitude();
	std::string AsString();

	Vector2D operator+ (const Vector2D &Other);
	Vector2D operator- (const Vector2D &Other);
	Vector2D operator* (const Vector2D &Other);
	Vector2D operator/ (const Vector2D &Other);

};

