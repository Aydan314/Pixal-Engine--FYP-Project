#include "CodeBlockParameter.h"

CodeBlockParameter::CodeBlockParameter(SDL_Renderer* renderer, Transform transform) : Block(renderer,transform)
{
	m_renderer = renderer;
	
	m_transform = transform;

	m_size = Vector2D(3,1);

	m_text = new GUIText(m_renderer, GameObjectData{ m_transform,COLLISION_NONE }, TextData{ m_name,ENGINE_FONT_PATH,15,{255,255,255,255} });

	m_hitboxes.push_back(Hitbox2D(&m_transform, Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE), m_renderer));


	CreateBlockOfSize(m_size);
}

CodeBlockParameter::~CodeBlockParameter()
{
}

void CodeBlockParameter::Render()
{
	for (SpriteSheetTile tile : m_textureTiles)
	{
		m_texture->Render((m_transform.position + tile.renderOffset) * m_transform.scale, SDL_FLIP_NONE, tile.cellPos.x, tile.cellPos.y, m_transform.rotation, m_transform.scale, m_colour);
	}
}

void CodeBlockParameter::CreateBlockOfSize(Vector2D size)
{
	for (int x = 0; x < size.x; x++) 
	{
		SpriteSheetTile tile;
		tile.renderOffset = Vector2D(x * CODE_BLOCK_TILE_SIZE, 0);

		int xVal = CODE_BLOCK_SHEET_PARAMETER_SEGMENT_X;

		if (x != 0) 
		{
			xVal ++;
			if (x == size.x - 1) 
			{
				xVal++;
			}
		}

		tile.cellPos = Vector2D(xVal, CODE_BLOCK_SHEET_PARAMETER_SEGMENT_Y);
		
		m_textureTiles.push_back(tile);
	}
}
