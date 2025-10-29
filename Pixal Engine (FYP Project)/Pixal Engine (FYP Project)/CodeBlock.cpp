#include "CodeBlock.h"

CodeBlock::CodeBlock(SDL_Renderer* renderer, Transform transform, SpriteSheetTexture ss_texture)
{
	m_renderer = renderer;
	m_ssTexture = ss_texture;
	m_transform = transform;
	m_size = { 10,3 };
	m_text = new GUIText(m_renderer, GameObjectData{ m_transform,COLLISION_NONE }, TextData{ m_name,ENGINE_FONT_PATH,30,{255,255,255,255} });
	
	Hitbox2D hitbox = Hitbox2D(&m_transform.position, Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, m_size.y * CODE_BLOCK_TILE_SIZE), m_renderer);
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
		m_texture->Render(m_transform.position + tile.renderOffset, SDL_FLIP_NONE, tile.cellPos.x,tile.cellPos.y, m_transform.rotation, m_transform.scale,m_colour);
	}
	m_text->Render();
	m_hitboxes[0].Draw();
}

void CodeBlock::Update(float deltaTime, SDL_Event e)
{
	if (CheckMouseCollision() && InputManager::Instance()->GetMouseLeftClicked()) 
	{
		m_hitboxes[0].SetColour({ 0,200,0,255 });
		m_transform.position = m_transform.position + InputManager::Instance()->GetMouseMovement();

		if (playAudio) 
		{
			AudioManager::Instance()->PlayAudio("Engine Sounds/CodeBlockPickup.wav");
			playAudio = false;
		}
	}
	else 
	{
		if (playAudio == false) 
		{
			AudioManager::Instance()->PlayAudio("Engine Sounds/CodeBlockPutdown.wav");
			playAudio = true;
		}

		m_hitboxes[0].SetColour({ 200,0,0,255 });
	}

	((GameObject*)m_text)->SetPosition(m_transform.position + Vector2D(CODE_BLOCK_TILE_SIZE / 2.f, ((m_size.y * CODE_BLOCK_TILE_SIZE) - m_text->GetRenderRect().h)/ 2.f));
	m_text->ReformatText();
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

void CodeBlock::CreateBlockOfSize(Vector2D size)
{
	for (int x = 0; x < size.x; x++) 
	{
		for (int y = 0; y < size.y; y++) 
		{
			SpriteSheetTile tile;
			tile.renderOffset = Vector2D(x * CODE_BLOCK_TILE_SIZE, y * CODE_BLOCK_TILE_SIZE);

			
			if (y == size.y - 1) 
			{
				tile.cellPos = tile.cellPos + Vector2D(0, 2);
			}
			else if (y != 0) 
			{
				tile.cellPos = tile.cellPos + Vector2D(0, 1);
			}

			if (x >= 1) 
			{
				tile.cellPos = tile.cellPos + Vector2D(1, 0);

				if (x == size.x - 1) 
				{
					tile.cellPos = tile.cellPos + Vector2D(5, 0);
				}
				else if (x >= 2) 
				{
					tile.cellPos = tile.cellPos + Vector2D(1, 0);
				}
			}


			m_textureTiles.push_back(tile);
			
		}
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

std::vector<Hitbox2D> CodeBlock::GetHitboxes()
{
	return m_hitboxes;
}

bool CodeBlock::CheckMouseCollision()
{
	Vector2D mousePos = InputManager::Instance()->GetMousePos();

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
