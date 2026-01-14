#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Commons.h"
#include "Texture2D.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Hitbox2D.h"
#include "Block.h"
#include "GUIText.h"
#include <iostream>

class CodeBlockParameter : public Block
{
protected:

	GUIText* m_text;
	std::string m_name = "PARAMETER";

	SDL_Color m_colour = { (Uint8)(rand() % 200),(Uint8)(rand() % 200),(Uint8)(rand() % 200), 255 };

	std::vector<SpriteSheetTile> m_textureTiles;


public:
	CodeBlockParameter(SDL_Renderer* renderer, Transform transform, BLOCK_ID ID = BLOCK_ID_CUSTOM);
	~CodeBlockParameter();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void CreateBlockOfSize(Vector2D size) override;
};

