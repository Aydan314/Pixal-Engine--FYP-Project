#include "CodeBlock.h"

CodeBlock::CodeBlock(SDL_Renderer* renderer, Transform transform) : Block(renderer, transform)
{
	m_renderer = renderer;
	
	m_transform = transform;

	m_textArea = Vector2D(8, 3);
	m_parameters = 2;

	m_size = m_textArea + Vector2D(CODE_BLOCK_PARAMETER_SEGMENT_SIZE * m_parameters, 0);

	m_mountPoint.position = Vector2D(0, (m_size.y * CODE_BLOCK_TILE_SIZE) - (CODE_BLOCK_TILE_SIZE / 2));
	m_mountPoint.used = false;

	m_text = new GUIText(m_renderer, GameObjectData{ m_transform,COLLISION_NONE }, TextData{ m_name,ENGINE_FONT_PATH,30,{255,255,255,255} });
	
	Hitbox2D hitbox = Hitbox2D(&m_transform, Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, m_size.y * CODE_BLOCK_TILE_SIZE), m_renderer);
	m_hitboxes.push_back(hitbox);

	CreateBlockOfSize(m_size);
}

CodeBlock::~CodeBlock()
{
}

void CodeBlock::Update(float deltaTime, SDL_Event e)
{
	((GameObject*)m_text)->SetScale(m_transform.scale);
	((GameObject*)m_text)->SetPosition(m_transform.position + Vector2D(CODE_BLOCK_TILE_SIZE / 2.f, ((m_size.y * CODE_BLOCK_TILE_SIZE) - (m_text->GetRenderRect().h / m_transform.scale.y))/ 2.f) );
	m_text->ReformatText();
}

void CodeBlock::Render()
{
	for (SpriteSheetTile tile : m_textureTiles)
	{
		m_texture->Render((m_transform.position + tile.renderOffset) * m_transform.scale, SDL_FLIP_NONE, tile.cellPos.x, tile.cellPos.y, m_transform.rotation, m_transform.scale, m_colour);
	}
	m_text->Render();
	//m_hitboxes[0].Draw();
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

std::vector<MountPoint>* CodeBlock::GetParameterMountPoints()
{
	return &m_paramPoints;
}