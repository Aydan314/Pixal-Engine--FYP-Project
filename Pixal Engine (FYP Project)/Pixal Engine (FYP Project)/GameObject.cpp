#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, SpriteSheetTexture ssTexture, GameObjectData gameObjectData)
{
	// Sets the default values //
	m_renderer = renderer;
	m_transform = gameObjectData.transform;
	m_collisionMode = gameObjectData.collisionMode;
	m_data = gameObjectData;
	m_ssTexture = ssTexture;
	playerCollision = false;

	m_size = { 0,0 };
	if (ssTexture.name != "")
	{
		// Gets the pre loaded texture from the texture loader //
		m_texture = new Texture2D(m_renderer);

		if (!m_texture->LoadStoredTexture(ssTexture.name, ssTexture.cellAmount.x, ssTexture.cellAmount.y))
		{
			std::cout << "!! Failed to load " << ssTexture.name << " !!\n";
		}

		m_collision_radius = m_texture->GetWidth() / 2.f;

		m_size = Vector2D(m_texture->GetWidth(), m_texture->GetHeight());
	}
}

GameObject::~GameObject()
{
	m_renderer = nullptr;
}

void GameObject::Render()
{
	m_texture->Render(GetPosition(), SDL_FLIP_NONE, m_ssTexture.cellPos.x, m_ssTexture.cellPos.y, m_transform.rotation, m_transform.scale);
}

void GameObject::Update(float deltaTime, SDL_Event e)
{

}

void GameObject::SetPosition(Vector2D position)
{
	m_transform.position = position;
}

void GameObject::SetPlayerCollision(bool state)
{
	playerCollision = state;
}

void GameObject::SetVisable(bool state)
{
	m_visable = state;
}

void GameObject::SetRotation(double rotation)
{
	m_transform.rotation = rotation;
}

void GameObject::LerpToLocation(Vector2D position, int duration)
{
	lerpDuration = duration;
	lerpTime = duration;
	lerpPosition = position;
	startPos = m_transform.position;
}

void GameObject::UpdateLerp(float deltaTime)
{
	if (lerpTime > 0)
	{
		m_transform.position.x = startPos.x + (lerpPosition.x - startPos.x) * (1 - (lerpTime / lerpDuration));
		m_transform.position.y = startPos.y + (lerpPosition.y - startPos.y) * (1 - (lerpTime / lerpDuration));

		lerpTime -= deltaTime * 1000.f;
	}
	else
	{
		lerpTime = 0;
	}
}

void GameObject::Delete()
{
	m_deleted = true;
}

Vector2D GameObject::GetPosition()
{
	return m_transform.position;
}

std::vector<Hitbox2D> GameObject::GetHitboxes()
{
	return m_hitboxes;
}

float GameObject::GetCollisionRadius()
{
	return m_collision_radius;
}

Vector2D GameObject::GetScale()
{
	return m_transform.scale;
}

COLLISION_MODE GameObject::GetCollisionMode()
{
	return m_collisionMode;
}

bool GameObject::GetVisable()
{
	return m_visable;
}

bool GameObject::GetPlayerCollision()
{
	return playerCollision;
}

bool GameObject::GetDeleted()
{
	return m_deleted;
}

bool GameObject::GetFinishedLerp()
{
	return lerpTime == 0;
}

double GameObject::GetRotation()
{
	return m_transform.rotation;
}

Transform GameObject::GetTransform()
{
	return m_transform;
}
