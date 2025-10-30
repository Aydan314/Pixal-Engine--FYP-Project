#pragma once
#include <iostream>
#include <vector>
#include "Constants.h"
#include "SDL.h"
#include "Vector2D.h"

enum COLLISION_MODE
{
	COLLISION_SINGLE,
	COLLISION_MULTIPLE,
	COLLISION_NONE,
	COLLISION_TRIGGER
};

struct Transform 
{
	Vector2D position;
	Vector2D scale;
	double rotation;
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float x_pos, float y_pos, float width, float height)
	{
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};

struct GameObjectData
{
	Transform transform;
	COLLISION_MODE collisionMode;
};

struct SpriteSheetTexture
{
	std::string name;
	Vector2D cellAmount;
	Vector2D cellPos;
};

struct TextureData
{
	std::string path;
	Vector2D size;
	SDL_Texture* texture = nullptr;
};

struct SpriteSheetTile 
{
	Vector2D cellPos;
	Vector2D renderOffset;
};

struct TextData
{
	std::string text;
	std::string fontPath;
	int size;
	SDL_Color colour;
};

struct ButtonColours
{
	SDL_Color defaultColour;
	SDL_Color selectedColour;
	SDL_Color clickedColour;
};

const std::vector<std::string> SOUNDS_TO_LOAD =
{
	{"Engine Sounds/CodeBlockPickup.wav","Engine Sounds/CodeBlockPutdown.wav","Engine Sounds/CodeBlockPickup.wav"}
};

const std::vector<SpriteSheetTexture> TEXTURES_TO_LOAD =
{
	{"Engine Images/CodeBlockSheet.png", {8,8}},{"Engine Images/EngineBackground.png",{1,1}}
};