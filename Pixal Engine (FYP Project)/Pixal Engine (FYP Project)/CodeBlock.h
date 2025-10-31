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

class CodeBlock
{
protected:
	SDL_Renderer* m_renderer = nullptr;
	CodeBlock* m_next = nullptr;
	CodeBlock* m_prev = nullptr;

	Vector2D m_size;
	Vector2D m_textArea;
	MountPoint m_mountPoint;
	std::vector<MountPoint> m_paramPoints;

	Transform m_transform;

	SpriteSheetTexture m_ssTexture = SpriteSheetTexture();

	Texture2D* m_texture;

	GUIText* m_text;
	std::string m_name = "CODE BLOCK";

	SDL_Color m_colour = { (Uint8)(rand() % 200),(Uint8)(rand() % 200),(Uint8)(rand() % 200), 255 };

	std::vector<SpriteSheetTile> m_textureTiles;
	std::vector<Hitbox2D> m_hitboxes;
	bool m_deleted = false;

	int m_parameters;
	

public:
	CodeBlock(SDL_Renderer* renderer, Transform transform, SpriteSheetTexture ss_texture);
	~CodeBlock();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void Delete();

	void SetPosition(Vector2D position);
	void SetRotation(double rotation);
	void SetScale(Vector2D scale);
	void SetNext(CodeBlock* next);
	virtual void CreateBlockOfSize(Vector2D size);

	void SnapTo(CodeBlock* other);
	void SnapFrom();

	Vector2D GetPosition();
	Vector2D GetScale();
	double GetRotation();
	Transform GetTransform();
	MountPoint* GetMountPoint();

	std::vector<Hitbox2D>* GetHitboxes();
	std::vector<MountPoint>* GetParameterMountPoints();

	virtual bool CheckMouseCollision();
	bool GetDeleted();
	

};

