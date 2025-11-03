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

struct MountPoint
{
	Vector2D position;
	bool used;
};

class Block
{
protected:
	Block* m_next = nullptr;
	Block* m_prev = nullptr;

	SDL_Renderer* m_renderer = nullptr;
	bool m_deleted = false;

	SDL_Color m_colour = { (Uint8)(rand() % 200),(Uint8)(rand() % 200),(Uint8)(rand() % 200), 255 };
	std::string m_name = "CODE BLOCK";

	Vector2D m_size;
	Transform m_transform;
	std::vector<Hitbox2D> m_hitboxes;
	MountPoint m_mountPoint;

	SpriteSheetTexture m_ssTexture = SpriteSheetTexture();
	std::vector<SpriteSheetTile> m_textureTiles;
	Texture2D* m_texture;

public:
	Block(SDL_Renderer* renderer, Transform transform);
	~Block();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void CreateBlockOfSize(Vector2D size);

	virtual void SnapTo(Block* other);
	virtual void SnapFrom();

	MountPoint* GetMountPoint();
	void SetNext(Block* next);

	bool CheckMouseCollision();
	std::vector<Hitbox2D>* GetHitboxes();

	void SetPosition(Vector2D position);
	void SetScale(Vector2D scale);
	void SetRotation(double rotation);

	Vector2D GetPosition();
	Vector2D GetScale();
	double GetRotation();
	Transform GetTransform();

	void Delete();
	bool GetDeleted();
};

