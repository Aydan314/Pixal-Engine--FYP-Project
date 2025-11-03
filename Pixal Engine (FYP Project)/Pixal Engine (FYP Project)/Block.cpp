#include "Block.h"

Block::Block(SDL_Renderer* renderer, Transform transform)
{
	m_renderer = renderer;
	m_transform = transform;

	m_ssTexture = SpriteSheetTexture{ "Engine Images/CodeBlockSheet.png",{8,8},{0,0} };

	// Gets the pre loaded texture from the texture loader //
	m_texture = new Texture2D(m_renderer);

	if (!m_texture->LoadStoredTexture(m_ssTexture.name, m_ssTexture.cellAmount.x, m_ssTexture.cellAmount.y))
	{
		std::cout << "!! Failed to load " << m_ssTexture.name << " !!\n";
	}
}

Block::~Block()
{
}

void Block::SnapTo(Block* other)
{
	if (!other->GetMountPoint()->used)
	{
		m_transform.position = other->GetMountPoint()->position + other->GetPosition();
		other->GetMountPoint()->used = true;
		other->SetNext(this);
		m_prev = other;
	}
}

void Block::SnapFrom()
{
	if (m_prev)
	{
		m_prev->GetMountPoint()->used = false;
		m_prev->SetNext(nullptr);
		m_prev = nullptr;
	}
}

void Block::SetNext(Block* next)
{
	m_next = next;
}

void Block::Render() 
{
	for (SpriteSheetTile tile : m_textureTiles)
	{
		m_texture->Render((m_transform.position + tile.renderOffset) * m_transform.scale, SDL_FLIP_NONE, tile.cellPos.x, tile.cellPos.y, m_transform.rotation, m_transform.scale, m_colour);
	}
}

void Block::SetPosition(Vector2D position) 
{
	m_transform.position = position;
}

void Block::SetScale(Vector2D scale)
{
	m_transform.scale = scale;
}

void Block::SetRotation(double rotation)
{
	m_transform.rotation = rotation;
}

Vector2D Block::GetPosition()
{
	return m_transform.position;
}

Vector2D Block::GetScale()
{
	return m_transform.scale;
}

double Block::GetRotation()
{
	return m_transform.rotation;
}

Transform Block::GetTransform()
{
	return m_transform;
}

void Block::Delete()
{
	m_deleted = true;
}

bool Block::GetDeleted()
{
	return m_deleted;
}

bool Block::CheckMouseCollision()
{
	Vector2D mousePos = InputManager::Instance()->GetMousePos();
	mousePos = mousePos / m_transform.scale;

	for (Hitbox2D hitbox : m_hitboxes)
	{
		if (hitbox.ContainsPoint(mousePos)) return true;
	}
	return false;
}

std::vector<Hitbox2D>* Block::GetHitboxes()
{
	return &m_hitboxes;
}

MountPoint* Block::GetMountPoint()
{
	return &m_mountPoint;
}

void Block::CreateBlockOfSize(Vector2D size)
{

}

void Block::Update(float deltaTime, SDL_Event e)
{

}

