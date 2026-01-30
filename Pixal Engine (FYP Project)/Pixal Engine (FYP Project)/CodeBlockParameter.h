#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Commons.h"
#include "Texture2D.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Hitbox2D.h"
#include "Block.h"
#include "GUITextBox.h"
#include <iostream>

class CodeBlockParameter : public Block
{
protected:

	GUITextBox* m_text;
	std::string m_name = "PARAMETER";
	std::string m_defaultText = m_name;
	DATA_TYPE m_dataType = DATA_TYPE_NONE;
	DataContent m_dataContent;

	SDL_Color m_colour = { (Uint8)(rand() % 200),(Uint8)(rand() % 200),(Uint8)(rand() % 200), 255 };

	std::vector<SpriteSheetTile> m_textureTiles;
	bool m_lastFocus = m_hasFocus;


public:
	CodeBlockParameter(SDL_Renderer* renderer, Transform transform, GameScene* gameScene, DATA_TYPE dataType = DATA_TYPE_NONE);
	~CodeBlockParameter();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void CreateBlock() override;
	void Init(DATA_TYPE type);
	void UpdateData();

	DATA_TYPE GetDataType();

	DataContent GetContents();
};

