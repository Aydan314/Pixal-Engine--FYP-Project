#include "CodeBlockParameter.h"

CodeBlockParameter::CodeBlockParameter(SDL_Renderer* renderer, Transform transform, BLOCK_ID ID) : Block(renderer,transform)
{
	m_type = BLOCK_TYPE_PARAMETER;
	m_renderer = renderer;
	
	m_transform = transform;

	m_size = Vector2D(3,1);

	m_text = new GUITextBox(m_renderer, Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE), GameObjectData{ m_transform,COLLISION_NONE }, TextData{ "",ENGINE_FONT_PATH,15,{255,255,255,255} });

	m_hitboxes.push_back(new Hitbox2D(&m_transform, Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE), Vector2D(0,0), m_renderer));

	m_startMountPoint = new MountPoint();
	m_endMountPoint = new MountPoint();
	m_conditionalMountPoint = nullptr;

	CreateBlockOfSize(m_size);
}

CodeBlockParameter::~CodeBlockParameter()
{
}

void CodeBlockParameter::Render()
{
	SDL_Color colour = m_colour;
	SDL_Color highlight = SDL_Color{ 20,20,20,255 };

	if (m_hasFocus) colour = SDL_Color
	{ 
		(Uint8)(m_colour.r + highlight.r), 
		(Uint8)(m_colour.g + highlight.g), 
		(Uint8)(m_colour.b + highlight.b), 
		m_colour.a 
	};

	for (SpriteSheetTile tile : m_textureTiles)
	{
		m_texture->Render((m_transform.position + tile.renderOffset) * m_transform.scale, SDL_FLIP_NONE, tile.cellPos.x, tile.cellPos.y, m_transform.rotation, m_transform.scale, colour);
	}
	m_text->Render();
}

void CodeBlockParameter::Update(float deltaTime, SDL_Event e)
{
	((GameObject*)m_text)->SetScale(m_transform.scale);
	((GameObject*)m_text)->SetPosition(m_transform.position + Vector2D(CODE_BLOCK_TILE_SIZE / 2.f, ((m_size.y * CODE_BLOCK_TILE_SIZE) - (m_text->GetRenderRect().h / m_transform.scale.y)) / 2.f));
	m_text->SetFocus(m_hasFocus);
	m_text->Update(deltaTime, e);
	m_text->ReformatText();
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
