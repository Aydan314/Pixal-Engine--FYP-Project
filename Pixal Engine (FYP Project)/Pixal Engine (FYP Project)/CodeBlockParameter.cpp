#include "CodeBlockParameter.h"

CodeBlockParameter::CodeBlockParameter(SDL_Renderer* renderer, Transform transform, GameScene* gameScene, DATA_TYPE dataType) : Block(renderer,transform,gameScene)
{
	m_type = BLOCK_TYPE_PARAMETER;
	m_renderer = renderer;
	
	m_transform = transform;

	m_size = Vector2D(3,1);

	m_dataType = dataType;
	Init(m_dataType);

	m_text = new GUITextBox(m_renderer, Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE), GameObjectData{ m_transform,COLLISION_NONE }, TextData{ m_defaultText,ENGINE_FONT_PATH,15,{255,255,255,255} });

	m_hitboxes.push_back(new Hitbox2D(&m_transform, Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE), Vector2D(0,0), m_renderer));

	m_startMountPoint = new MountPoint();
	m_endMountPoint = new MountPoint();
	m_conditionalMountPoint = nullptr;

	m_dataContent.gameObject = nullptr;
	m_dataContent.string = "";
	m_dataContent.number = 0;

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

	if (!m_hasFocus && m_lastFocus) UpdateData();
	m_lastFocus = m_hasFocus;
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

void CodeBlockParameter::Init(DATA_TYPE type)
{
	switch (type) 
	{
	case DATA_TYPE_NUMBER:
		m_colour = SDL_Color{ 50,50,225,255 };
		m_defaultText = "0";
		break;
	case DATA_TYPE_GAMEOBJECT:
		m_colour = SDL_Color{ 50,225,50,255 };
		m_defaultText = "GAMEOBJECT";
		break;
	case DATA_TYPE_STRING:
		m_colour = SDL_Color{ 235,180,50,255 };
		m_defaultText = "Hello";
		break;
	}
}

void CodeBlockParameter::UpdateData()
{
	switch (m_dataType)
	{
	case DATA_TYPE_NUMBER:
		m_dataContent.number = std::stof(m_text->GetText());
		break;
	case DATA_TYPE_GAMEOBJECT:
		
		break;
	case DATA_TYPE_STRING:
		
		m_dataContent.string = m_text->GetText();
		break;
	}
}

DATA_TYPE CodeBlockParameter::GetDataType()
{
	return m_dataType;
}

float CodeBlockParameter::GetNumberData()
{
	return m_dataContent.number;
}

std::string CodeBlockParameter::GetStringData()
{
	return m_dataContent.string;
}

GameObject* CodeBlockParameter::GetGameObjectData()
{
	return m_dataContent.gameObject;
}
