#include "CodeBlockParameter.h"

CodeBlockParameter::CodeBlockParameter(SDL_Renderer* renderer, Transform transform, SpriteSheetTexture ss_texture) : CodeBlock(renderer,transform,ss_texture)
{
	m_renderer = renderer;
	m_ssTexture = ss_texture;
	m_transform = transform;

	m_size = Vector2D(3,1);

	m_text = new GUIText(m_renderer, GameObjectData{ m_transform,COLLISION_NONE }, TextData{ m_name,ENGINE_FONT_PATH,15,{255,255,255,255} });

	m_hitbox = Hitbox2D(&m_transform, Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE), m_renderer);

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

CodeBlockParameter::~CodeBlockParameter()
{
}

//void CodeBlockParameter::CreateBlockOfSize(Vector2D size)
//{
//	for (int x = 0; x < size.x; x++) 
//	{
//		SpriteSheetTile tile;
//		tile.renderOffset = Vector2D(x * CODE_BLOCK_TILE_SIZE, 0);
//
//		int xVal = CODE_BLOCK_SHEET_PARAMETER_SEGMENT_X;
//
//		if (x != 0) 
//		{
//			xVal ++;
//			if (x == size.x - 1) 
//			{
//				xVal++;
//			}
//		}
//
//		tile.cellPos = Vector2D(xVal, CODE_BLOCK_SHEET_PARAMETER_SEGMENT_Y);
//		
//		m_textureTiles.push_back(tile);
//	}
//}

Hitbox2D* CodeBlockParameter::GetHitbox()
{
	return &m_hitbox;
}

bool CodeBlockParameter::CheckMouseCollision()
{
	Vector2D mousePos = InputManager::Instance()->GetMousePos();
	mousePos = mousePos / m_transform.scale;

	return m_hitbox.ContainsPoint(mousePos);
}
