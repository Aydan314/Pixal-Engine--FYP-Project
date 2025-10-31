#include "CodeBlock.h"

CodeBlock::CodeBlock(SDL_Renderer* renderer, Transform transform, SpriteSheetTexture ss_texture)
{
	m_renderer = renderer;
	m_ssTexture = ss_texture;
	m_transform = transform;

	m_textArea = Vector2D(8, 3);
	m_parameters = 2;

	m_size = m_textArea + Vector2D(CODE_BLOCK_PARAMETER_SEGMENT_SIZE * m_parameters, 0);

	m_mountPoint.position = Vector2D(0, (m_size.y * CODE_BLOCK_TILE_SIZE) - (CODE_BLOCK_TILE_SIZE / 2));
	m_mountPoint.used = false;

	m_text = new GUIText(m_renderer, GameObjectData{ m_transform,COLLISION_NONE }, TextData{ m_name,ENGINE_FONT_PATH,30,{255,255,255,255} });
	
	Hitbox2D hitbox = Hitbox2D(&m_transform, Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, m_size.y * CODE_BLOCK_TILE_SIZE), m_renderer);
	m_hitboxes.push_back(hitbox);

	if (ss_texture.name != "")
	{
		// Gets the pre loaded texture from the texture loader //
		m_texture = new Texture2D(m_renderer);

		if (!m_texture->LoadStoredTexture(ss_texture.name, ss_texture.cellAmount.x, ss_texture.cellAmount.y))
		{
			std::cout << "!! Failed to load " << ss_texture.name << " !!\n";
		}
	}
	else std::cout << "!! Invalid texture name !!\n";

	CreateBlockOfSize(m_size);
}

CodeBlock::~CodeBlock()
{
}

void CodeBlock::Render()
{
	for (SpriteSheetTile tile : m_textureTiles) 
	{
		m_texture->Render((m_transform.position + tile.renderOffset) * m_transform.scale, SDL_FLIP_NONE, tile.cellPos.x,tile.cellPos.y, m_transform.rotation, m_transform.scale,m_colour);
	}
	m_text->Render();
	m_hitboxes[0].Draw();
}

void CodeBlock::Update(float deltaTime, SDL_Event e)
{
	
	((GameObject*)m_text)->SetScale(m_transform.scale);
	((GameObject*)m_text)->SetPosition(m_transform.position + Vector2D(CODE_BLOCK_TILE_SIZE / 2.f, ((m_size.y * CODE_BLOCK_TILE_SIZE) - (m_text->GetRenderRect().h / m_transform.scale.y))/ 2.f) );
	m_text->ReformatText();
}

void CodeBlock::Delete()
{
	m_deleted = true;
}

void CodeBlock::SetPosition(Vector2D position)
{
	m_transform.position = position;
}

void CodeBlock::SetRotation(double rotation)
{
	m_transform.rotation = rotation;
}

void CodeBlock::SetScale(Vector2D scale)
{
	m_transform.scale = scale;
}

void CodeBlock::SetNext(CodeBlock* next)
{
	m_next = next;
}

void CodeBlock::CreateBlockOfSize(Vector2D size)
{
	m_paramPoints.clear();

	int xVal = 0;
	// Create Start Of Code Block //
	for (xVal; xVal < 2; xVal++) 
	{
		for (int y = 0; y < size.y; y++)
		{
			SpriteSheetTile tile;
			tile.renderOffset = Vector2D(xVal * CODE_BLOCK_TILE_SIZE, y * CODE_BLOCK_TILE_SIZE);


			int yVal = 0;

			if (y != 0 && y < size.y - 1) 
			{
				yVal = 1;
			}
			else if (y == size.y - 1) 
			{
				yVal = 2;
			}

			tile.cellPos = Vector2D(xVal, yVal);

			m_textureTiles.push_back(tile);
		}
	}

	// Create Segment For Text //

	for (xVal; xVal < (m_textArea.x - 1); xVal++)
	{
		for (int y = 0; y < size.y; y++)
		{
			SpriteSheetTile tile;
			tile.renderOffset = Vector2D(xVal * CODE_BLOCK_TILE_SIZE, y * CODE_BLOCK_TILE_SIZE);

			int yVal = 0;

			if (y != 0 && y < size.y - 1)
			{
				yVal = 1;
			}
			else if (y == size.y - 1)
			{
				yVal = 2;
			}

			tile.cellPos = Vector2D(CODE_BLOCK_SHEET_TEXT_SEGMENT, yVal);

			m_textureTiles.push_back(tile);
		}
	}

	// Create Parameter Sections //
	for (int i = 0; i < m_parameters; i++) 
	{
		MountPoint point;
		point.position = Vector2D(xVal * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE);
		point.used = false;
		m_paramPoints.push_back(point);

		for (int x = 0; x < CODE_BLOCK_PARAMETER_SEGMENT_SIZE; x++)
		{
			for (int y = 0; y < size.y; y++)
			{
				SpriteSheetTile tile;
				tile.renderOffset = Vector2D(xVal * CODE_BLOCK_TILE_SIZE, y * CODE_BLOCK_TILE_SIZE);

				int yVal = 0;

				if (y != 0 && y < size.y - 1)
				{
					yVal = 1;
				}
				else if (y == size.y - 1)
				{
					yVal = 2;
				}

				tile.cellPos = Vector2D(x + 2, yVal);

				m_textureTiles.push_back(tile);
			}
			xVal++;
		}
	}

	// Finish Code Block //
	for (int y = 0; y < size.y; y++) 
	{
		SpriteSheetTile tile;
		tile.renderOffset = Vector2D(xVal * CODE_BLOCK_TILE_SIZE, y * CODE_BLOCK_TILE_SIZE);

		int yVal = 0;

		if (y != 0 && y < size.y - 1)
		{
			yVal = 1;
		}
		else if (y == size.y - 1)
		{
			yVal = 2;
		}

		tile.cellPos = Vector2D(CODE_BLOCK_SHEET_END_SEGMENT, yVal);

		m_textureTiles.push_back(tile);
	}
	


}

void CodeBlock::SnapTo(CodeBlock* other)
{
	if (!other->GetMountPoint()->used) 
	{
		m_transform.position = other->GetMountPoint()->position + other->GetPosition();
		other->GetMountPoint()->used = true;
		other->SetNext(this);
		m_prev = other;
	}
}

void CodeBlock::SnapFrom()
{
	if (m_prev) 
	{
		m_prev->GetMountPoint()->used = false;
		m_prev->SetNext(nullptr);
		m_prev = nullptr;
	}
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

MountPoint* CodeBlock::GetMountPoint()
{
	return &m_mountPoint;
}

std::vector<Hitbox2D>* CodeBlock::GetHitboxes()
{
	return &m_hitboxes;
}

std::vector<MountPoint>* CodeBlock::GetParameterMountPoints()
{
	return &m_paramPoints;
}

bool CodeBlock::CheckMouseCollision()
{
	Vector2D mousePos = InputManager::Instance()->GetMousePos();
	mousePos = mousePos / m_transform.scale;

	for (Hitbox2D hitbox : m_hitboxes)
	{
		if (hitbox.ContainsPoint(mousePos)) return true;
	}
	return false;
}

bool CodeBlock::GetDeleted()
{
	return m_deleted;
}
