#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>

class CodeBlock
{
protected:
	SDL_Renderer* m_renderer = nullptr;

	Vector2D m_size = { 0.f,0.f };

	Transform m_transform;

	SpriteSheetTexture m_ssTexture = SpriteSheetTexture();
	
	std::vector<Rect2D> m_hitboxes;
	bool m_deleted = false;

public:
	CodeBlock(SDL_Renderer* renderer, SpriteSheetTexture ss_texture);
	~CodeBlock();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void Delete();

	void SetPosition(Vector2D position);
	void SetRotation(double rotation);

	Vector2D GetPosition();
	Vector2D GetScale();
	double GetRotation();
	Transform GetTransform();

	std::vector<Rect2D> GetHitboxes();
	
	bool GetDeleted();
	

};

