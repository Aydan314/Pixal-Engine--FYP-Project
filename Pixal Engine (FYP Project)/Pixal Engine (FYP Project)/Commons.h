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

enum BLOCK_TYPE 
{
	BLOCK_TYPE_NONE,
	BLOCK_TYPE_BLOCK,
	BLOCK_TYPE_PARAMETER
};

enum BLOCK_ID 
{
	BLOCK_ID_CUSTOM,
	BLOCK_ID_SET_POSITION,
	BLOCK_ID_STOP,
	BLOCK_ID_START,
	BLOCK_ID_IF,
	BLOCK_ID_CREATE_GAMEOBJECT,

	BLOCK_ID_END_ID
};

enum MOUNT_TYPE 
{
	MOUNT_TYPE_UNDEFINED,
	MOUNT_TYPE_START,
	MOUNT_TYPE_CONDITIONAL,
	MOUNT_TYPE_END
};

enum DATA_TYPE 
{
	DATA_TYPE_NONE,
	DATA_TYPE_STRING,
	DATA_TYPE_NUMBER,
	DATA_TYPE_GAMEOBJECT
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
	{"Engine Images/CodeBlockSheet.png", {8,8}},{"Engine Images/EngineBackground.png",{1,1}},{"Engine Images/Sprites.png",{2,2}}
};

const SDL_Color ENGINE_BACKGROUND_COLOUR = { 50,50,50,255 };
const SDL_Color ENGINE_TEXT_COLOUR = { 255,255,255,255 };

const ButtonColours ENGINE_BUTTON_COLOURS
{
	SDL_Color{50,50,90,255},
	SDL_Color{80,80,120,255},
	SDL_Color{100,100,140,255}
};