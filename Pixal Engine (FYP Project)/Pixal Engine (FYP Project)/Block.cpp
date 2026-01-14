#include "Block.h"

Block::Block(SDL_Renderer* renderer, Transform transform, BLOCK_ID ID)
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
	if (!m_startBlock) 
	{
		if (m_type == BLOCK_TYPE_PARAMETER && other->GetType() == BLOCK_TYPE_BLOCK)
		{
			if (!m_prev) other->AttachParameter(this);
		}
		else
		{
			if (other->GetMountPoint()->contents == nullptr && !other->IsEndBlock())
			{
				other->SetNext(this);
				m_prev = other;
			}
		}
	}
}

void Block::SnapFrom()
{
	if (m_prev) 
	{
		if (m_type == BLOCK_TYPE_PARAMETER)
		{

			for (MountPoint* item : m_prev->m_paramPoints)
			{
				if (item->contents == this)
				{
					item->contents = nullptr;
					break;
				}
			}
			m_prev = nullptr;
		}
		else
		{
			m_prev->GetMountPoint()->contents = nullptr;
			m_prev->SetNext(nullptr);
			m_prev = nullptr;
		}
	}
}

void Block::AttachParameter(Block* block)
{

	for (MountPoint* point : m_paramPoints)
	{
		if (point->contents == nullptr) 
		{
			Vector2D dist = (m_transform.position + point->position) - block->GetPosition();
			float distance = dist.Magnitude();

			if (distance <= (CODE_BLOCK_PARAMETER_SEGMENT_SIZE * CODE_BLOCK_TILE_SIZE))
			{
				point->contents = block;
				block->SetPrev(this);
				break;
			}
		}
	}
}

void Block::SetNext(Block* next)
{
	m_next = next;
	m_mountPoint.contents = next;
	Resize();
}

void Block::SetPrev(Block* prev)
{
	m_prev = prev;
}

Block* Block::GetNext()
{
	return m_next;
}

Block* Block::GetPrev()
{
	return m_prev;
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

bool Block::IsStartBlock()
{
	return m_startBlock;
}

bool Block::IsEndBlock()
{
	return m_endBlock;
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

BLOCK_TYPE Block::GetType()
{
	return m_type;
}

void Block::CreateBlockOfSize(Vector2D size)
{

}

void Block::Resize()
{
}

void Block::Update(float deltaTime, SDL_Event e)
{
	
}

