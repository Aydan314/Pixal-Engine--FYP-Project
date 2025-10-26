#include "CodeBlock.h"

CodeBlock::CodeBlock(SDL_Renderer* renderer, SpriteSheetTexture ss_texture)
{
	m_renderer = renderer;
	m_ssTexture = ss_texture;
}

CodeBlock::~CodeBlock()
{
}

void CodeBlock::Render()
{
	//m_texture->Render(GetPosition(), SDL_FLIP_NONE, m_ssTexture.cellPos.x, m_ssTexture.cellPos.y, m_transform.rotation, m_transform.scale);
	SDL_Rect a = { m_transform.position.x, m_transform.position.y, 100.f, 100.f };
	SDL_RenderDrawRect(m_renderer, &a);
}

void CodeBlock::Update(float deltaTime, SDL_Event e)
{
}

void CodeBlock::Delete()
{
	m_deleted = true;
}

void CodeBlock::SetPosition(Vector2D position)
{
}

void CodeBlock::SetRotation(double rotation)
{
}

Vector2D CodeBlock::GetPosition()
{
	return m_transform.position;
}

Vector2D CodeBlock::GetScale()
{
	return m_transform.scale;
}

double CodeBlock::GetRotation()
{
	return m_transform.rotation;
}

Transform CodeBlock::GetTransform()
{
	return m_transform;
}

std::vector<Rect2D> CodeBlock::GetHitboxes()
{
	return m_hitboxes;
}

bool CodeBlock::GetDeleted()
{
	return m_deleted;
}
