#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Hitbox2D.h"
#include "InputManager.h"
#include <iostream>

class GameObject
{
protected:
	SDL_Renderer* m_renderer = nullptr;

	Vector2D m_size = { 0.f,0.f };
	
	Transform m_transform;
	
	SpriteSheetTexture m_ssTexture = SpriteSheetTexture();
	Texture2D* m_texture = nullptr;
	GameObjectData m_data = GameObjectData();

	float m_collision_radius;
	COLLISION_MODE m_collisionMode;
	std::vector<Hitbox2D> m_hitboxes;

	bool playerCollision = false;
	bool m_visable = true;
	bool m_deleted = false;
	
	float lerpDuration = 0.f;
	float lerpTime = 0.f;
	Vector2D lerpPosition = { 0.f,0.f };
	Vector2D startPos = { 0.f,0.f };

private:

public:
	GameObject(SDL_Renderer* renderer, SpriteSheetTexture ss_texture, GameObjectData gameObjectData);
	~GameObject();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void LerpToLocation(Vector2D position, int duration);
	void UpdateLerp(float deltaTime);
	void Delete();

	void SetPosition(Vector2D position);
	void SetRotation(double rotation);
	void SetScale(Vector2D scale);

	void SetPlayerCollision(bool state);
	void SetVisable(bool state);
	

	Vector2D GetPosition();
	Vector2D GetScale();
	double GetRotation();
	Transform GetTransform();

	Rect2D GetScreenSpaceRect() { return Rect2D(m_transform.position.x, m_transform.position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
	std::vector<Hitbox2D> GetHitboxes();
	float GetCollisionRadius();
	
	COLLISION_MODE GetCollisionMode();
	bool GetVisable();
	bool GetPlayerCollision();
	bool GetDeleted();
	bool GetFinishedLerp();
	
};


