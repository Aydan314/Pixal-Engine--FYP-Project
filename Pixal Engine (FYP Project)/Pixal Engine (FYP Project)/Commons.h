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
	BLOCK_ID_STOP,
	BLOCK_ID_START,
	BLOCK_ID_CREATE_GAMEOBJECT,
	BLOCK_ID_SET_POSITION,
	BLOCK_ID_SET_VELOCITY,
	BLOCK_ID_SET_FRICTION,
	BLOCK_ID_SWITCH_SPRITE,
	BLOCK_ID_IF_EQUAL,
	BLOCK_ID_IF_LESS,
	BLOCK_ID_IF_MORE,
	BLOCK_ID_ON_KEY,
	BLOCK_ID_ON_TICK,
	BLOCK_ID_ON_COLLISION,
	BLOCK_ID_GET_X,
	BLOCK_ID_GET_Y,
	BLOCK_ID_CREATE_TEXTOBJECT,
	BLOCK_ID_SET_TEXT,
	BLOCK_ID_JOIN,
	BLOCK_ID_ADD,
	BLOCK_ID_MINUS,
	BLOCK_ID_TIMES,
	BLOCK_ID_DIVIDE,
	

	BLOCK_ID_END_ID
};

enum OBJECT_TYPE 
{
	OBJECT_UNDEFINED,
	OBJECT_GAMEOBJECT,
	OBJECT_GUICANVAS,
	OBJECT_GUITEXT,
	OBJECT_GUITEXTBLOCK,
	OBJECT_GUITEXTBOX,
	OBJECT_GUIBUTTON
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
	DATA_TYPE_VARIABLE,
	DATA_TYPE_STRING,
	DATA_TYPE_NUMBER,
	DATA_TYPE_GAMEOBJECT,

	DATA_TYPE_MAX
};

struct Transform 
{
	Vector2D position;
	Vector2D scale;
	double rotation;
};

struct PhysicsBody 
{
	Vector2D velocity;
	float friction;
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

class GameObject;

struct DataContent
{
	std::string name;
	float number;
	std::string string;
	GameObject* gameObject;
	DATA_TYPE dataType;
};

const std::vector<std::string> SOUNDS_TO_LOAD =
{
	{"Engine Sounds/CodeBlockPickup.wav","Engine Sounds/CodeBlockPutdown.wav","Engine Sounds/CodeBlockPickup.wav"}
};

const std::vector<SpriteSheetTexture> TEXTURES_TO_LOAD =
{
	{"Engine Images/CodeBlockSheet.png", {8,8}},{"Engine Images/EngineBackground.png",{1,1}},{"Engine Images/Sprites.png",{2,2}},{"Engine Images/Sprites Large.png",{4,1}}
};

const SDL_Color ENGINE_BACKGROUND_COLOUR = { 50,50,50,255 };
const SDL_Color ENGINE_RUNNING_COLOUR = { 50,150,50,255 };
const SDL_Color ENGINE_TEXT_COLOUR = { 255,255,255,255 };

const ButtonColours ENGINE_BUTTON_COLOURS
{
	SDL_Color{50,50,90,255},
	SDL_Color{80,80,120,255},
	SDL_Color{100,100,140,255}
};