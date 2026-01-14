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

class Block;

struct MountPoint
{
	Vector2D position;
	Block* contents;
	MOUNT_TYPE type;
};

class Block
{
protected:
	bool m_startBlock = false;
	bool m_endBlock = false;
	bool m_conditionalBlock = false;

	SDL_Renderer* m_renderer = nullptr;
	bool m_deleted = false;
	BLOCK_TYPE m_type = BLOCK_TYPE_NONE;
	std::vector<MountPoint*> m_paramPoints;

	SDL_Color m_colour = COLOUR_BLUE;
	std::string m_name = "CODE BLOCK";

	Vector2D m_size;
	Transform m_transform;
	std::vector<Hitbox2D*> m_hitboxes;

	MountPoint* m_endMountPoint;
	MountPoint* m_startMountPoint;
	MountPoint* m_conditionalMountPoint;

	SpriteSheetTexture m_ssTexture = SpriteSheetTexture();
	std::vector<SpriteSheetTile> m_textureTiles;
	Texture2D* m_texture;

public:
	Block(SDL_Renderer* renderer, Transform transform, BLOCK_ID ID = BLOCK_ID_CUSTOM);
	~Block();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void CreateBlockOfSize(Vector2D size);
	virtual void Resize();

	virtual void SnapTo(Block* other);
	virtual void SnapFrom();
	void AttachParameter(Block* block);

	MountPoint* GetMountPoint();
	MountPoint* GetConditionalMountpoint();

	BLOCK_TYPE GetType();
	void SetNext(Block* next);
	void SetPrev(Block* prev);
	void SetConditional(Block* conditional);

	Block* GetNext();
	Block* GetPrev();

	bool CheckMouseCollision();
	std::vector<Hitbox2D*> GetHitboxes();

	void SetPosition(Vector2D position);
	void SetScale(Vector2D scale);
	void SetRotation(double rotation);

	Vector2D GetPosition();
	Vector2D GetScale();
	double GetRotation();
	Transform GetTransform();

	bool IsStartBlock();
	bool IsEndBlock();
	bool IsConditionalBlock();

	void Delete();
	bool GetDeleted();
};

