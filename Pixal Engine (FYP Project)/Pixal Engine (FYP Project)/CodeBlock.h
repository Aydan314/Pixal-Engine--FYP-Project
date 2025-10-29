#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Commons.h"
#include "Texture2D.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Hitbox2D.h"
#include "GUIText.h"
#include <iostream>

class CodeBlock
{
protected:
	SDL_Renderer* m_renderer = nullptr;

	Vector2D m_size = { 0.f,0.f };

	Transform m_transform;

	SpriteSheetTexture m_ssTexture = SpriteSheetTexture();

	Texture2D* m_texture;

	GUIText* m_text;
	std::string m_name = "CODE BLOCK";

	SDL_Color m_colour = { (Uint8)(rand() % 200),(Uint8)(rand() % 200),(Uint8)(rand() % 200), 255 };

	std::vector<SpriteSheetTile> m_textureTiles;
	std::vector<Hitbox2D> m_hitboxes;
	bool m_deleted = false;
	bool playAudio = true;

public:
	CodeBlock(SDL_Renderer* renderer, Transform transform, SpriteSheetTexture ss_texture);
	~CodeBlock();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void Delete();

	void SetPosition(Vector2D position);
	void SetRotation(double rotation);
	void CreateBlockOfSize(Vector2D size);

	Vector2D GetPosition();
	Vector2D GetScale();
	double GetRotation();
	Transform GetTransform();

	std::vector<Hitbox2D> GetHitboxes();

	bool CheckMouseCollision();
	bool GetDeleted();
	

};

