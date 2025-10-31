#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Commons.h"
#include "Texture2D.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Hitbox2D.h"
#include "CodeBlock.h"
#include "GUIText.h"
#include <iostream>

class CodeBlockParameter : public CodeBlock
{
protected:
	SDL_Renderer* m_renderer = nullptr;

	Transform m_transform;

	SpriteSheetTexture m_ssTexture = SpriteSheetTexture();

	Texture2D* m_texture;

	GUIText* m_text;
	std::string m_name = "PARAMETER";

	SDL_Color m_colour = { (Uint8)(rand() % 200),(Uint8)(rand() % 200),(Uint8)(rand() % 200), 255 };

	std::vector<SpriteSheetTile> m_textureTiles;
	Hitbox2D m_hitbox;
	bool m_deleted = false;

	int m_parameters;


public:
	CodeBlockParameter(SDL_Renderer* renderer, Transform transform, SpriteSheetTexture ss_texture);
	~CodeBlockParameter();

	//void CreateBlockOfSize(Vector2D size);

	Hitbox2D* GetHitbox();

	bool CheckMouseCollision() override;


};

