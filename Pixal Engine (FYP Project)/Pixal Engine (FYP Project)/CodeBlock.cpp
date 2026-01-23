#include "CodeBlock.h"

CodeBlock::CodeBlock(SDL_Renderer* renderer, Transform transform, GameScene* gameScene, BLOCK_ID ID) : Block(renderer, transform, gameScene)
{
	m_type = BLOCK_TYPE_BLOCK;
	m_ID = ID;
	m_renderer = renderer;
	m_transform = transform;

	Init(ID);
	CreateBlockOfSize(m_size);
}

CodeBlock::~CodeBlock()
{
}

void CodeBlock::Init(BLOCK_ID ID)
{
	m_textArea = Vector2D(8, CODE_BLOCK_HEIGHT);
	m_parameters = 0;

	switch (ID) 
	{

	case BLOCK_ID_SET_POSITION:
		m_name = "Set Position";
		m_colour = COLOUR_GREEN;

		m_parameters = 1;
		m_textArea = Vector2D(6, CODE_BLOCK_HEIGHT);
		break;

	case BLOCK_ID_IF:
		m_name = "If";
		m_colour = COLOUR_LIGHT_GREY;

		m_parameters = 1;
		m_textArea = Vector2D(6, CODE_BLOCK_HEIGHT);
		m_conditionalBlock = true;
		break;

	case BLOCK_ID_STOP:
		m_name = "Stop";
		m_colour = COLOUR_RED;

		m_parameters = 0;
		m_textArea = Vector2D(6, CODE_BLOCK_HEIGHT);
		m_endBlock = true;
		break;

	case BLOCK_ID_START:
		m_name = "On Start";
		m_colour = COLOUR_GREEN;

		m_parameters = 0;
		m_textArea = Vector2D(6, CODE_BLOCK_HEIGHT);
		m_startBlock = true;
		break;

	case BLOCK_ID_CREATE_GAMEOBJECT:
		m_name = "Create GameObject";
		m_colour = COLOUR_GREEN;

		m_parameters = 1;
		m_textArea = Vector2D(7, CODE_BLOCK_HEIGHT);
		break;
	}


	m_text = new GUIText(m_renderer, GameObjectData{ m_transform,COLLISION_NONE }, TextData{ m_name,ENGINE_FONT_PATH,30,{255,255,255,255} });

	m_size = m_textArea + Vector2D(CODE_BLOCK_PARAMETER_SEGMENT_SIZE * m_parameters, 0);

	Hitbox2D* hitbox = new Hitbox2D(&m_transform, Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, m_size.y * CODE_BLOCK_TILE_SIZE), Vector2D(0,0), m_renderer);
	m_hitboxes.push_back(hitbox);

	InitMountPoints();
	
}

void CodeBlock::InitMountPoints()
{
	m_startMountPoint = new MountPoint();
	m_startMountPoint->type = MOUNT_TYPE_START;

	m_conditionalMountPoint = nullptr;
	if (m_conditionalBlock)
	{
		m_conditionalMountPoint = new MountPoint();
		m_conditionalMountPoint->position = Vector2D(CODE_BLOCK_TILE_SIZE, (m_size.y * CODE_BLOCK_TILE_SIZE) - (CODE_BLOCK_TILE_SIZE / 2));
		m_conditionalMountPoint->type = MOUNT_TYPE_CONDITIONAL;

		m_endHitbox = new Hitbox2D
		(
			&m_transform,
			Vector2D(m_size.x * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE),
			Vector2D(0, (CODE_BLOCK_HEIGHT + CODE_BLOCK_CONDITIONAL_TAIL_LENGTH) * CODE_BLOCK_TILE_SIZE),
			m_renderer
		);

		m_hitboxes.push_back(m_endHitbox);
	}

	m_endMountPoint = new MountPoint();
	m_endMountPoint->contents = nullptr;
	m_endMountPoint->position = Vector2D(0, (m_size.y * CODE_BLOCK_TILE_SIZE) - (CODE_BLOCK_TILE_SIZE / 2));
	m_endMountPoint->type = MOUNT_TYPE_END;
}

void CodeBlock::Update(float deltaTime, SDL_Event e)
{
	for (MountPoint* item : m_paramPoints)
	{
		if (item->contents != nullptr) item->contents->SetPosition(item->position + this->GetPosition());
	}
	if (m_endMountPoint->contents != nullptr) 
	{
		m_endMountPoint->contents->SetPosition(m_endMountPoint->position + this->GetPosition());
	}

	if (m_conditionalBlock) 
	{
		float yPos = (CODE_BLOCK_HEIGHT + CODE_BLOCK_CONDITIONAL_TAIL_LENGTH) * CODE_BLOCK_TILE_SIZE;
		if (m_conditionalMountPoint->contents != nullptr) yPos = (CODE_BLOCK_HEIGHT + m_tailTextureTiles.size()) * CODE_BLOCK_TILE_SIZE;
			
		m_endHitbox->SetPosition(Vector2D(0, yPos));

		if (m_conditionalMountPoint->contents != nullptr)
		{
			m_conditionalMountPoint->contents->SetPosition(m_conditionalMountPoint->position + this->GetPosition());
		}
	}

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
	if (m_conditionalBlock) 
	{
		for (SpriteSheetTile tile : m_tailTextureTiles)
		{
			m_texture->Render((m_transform.position + tile.renderOffset) * m_transform.scale, SDL_FLIP_NONE, tile.cellPos.x, tile.cellPos.y, m_transform.rotation, m_transform.scale, m_colour);
		}
		for (SpriteSheetTile tile : m_tailEndTextureTiles)
		{
			m_texture->Render((m_transform.position + tile.renderOffset + m_endHitbox->GetPosition()) * m_transform.scale, SDL_FLIP_NONE, tile.cellPos.x, tile.cellPos.y, m_transform.rotation, m_transform.scale, m_colour);
		}
	}
	m_text->Render();

	/*for (int i = 0; i < m_hitboxes.size(); i++) 
	{
		m_hitboxes[i]->Draw();
	}*/
}

void CodeBlock::Resize()
{
	if (m_conditionalBlock)
	{
		m_tailTextureTiles = {};
		CreateTail();
	}
	else if (m_startMountPoint->contents != nullptr) m_startMountPoint->contents->Resize();
}

void CodeBlock::Run()
{
	switch (m_ID) 
	{
	case BLOCK_ID_SET_POSITION:
		std::cout << "Set Position to: ";
		if (m_paramPoints[0]->contents) std::cout << ((CodeBlockParameter*)m_paramPoints[0]->contents)->GetNumberData();
		std::cout << "\n";
		break;
	case BLOCK_ID_CREATE_GAMEOBJECT:
		
		m_gameScene->Add(new GameObject
			(
			m_gameScene->GetRenderer(),
			SpriteSheetTexture{ "Engine Images/Sprites.png", {2,2},{0,0} },
			GameObjectData{ Transform{ {0,0},{1,1},0 },COLLISION_SINGLE }
			)
		);
		break;

	default:
		std::cout << m_name << "\n";
		break;
	}
	
	if (GetNext()) GetNext()->Run();
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

			// Remove top connection //
			if (m_startBlock && xVal == 1 && yVal == 0) 
			{
				tile.cellPos = Vector2D(2, yVal);
			}
			// Remove bottom connection //
			else if (m_endBlock && xVal == 1 && yVal == 2)
			{
				tile.cellPos = Vector2D(2, yVal);
			}
			// Start tail //
			else if (m_conditionalBlock && yVal == 2 && xVal == 0) 
			{
				tile.cellPos = Vector2D(xVal, 3);
			}
			else if (m_conditionalBlock && yVal == 2 && xVal == 1)
			{
				tile.cellPos = Vector2D(2, yVal);
			}
			else tile.cellPos = Vector2D(xVal, yVal);

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

			if (m_conditionalBlock && xVal == 2 && yVal == 2) 
			{
				tile.cellPos = Vector2D(1, yVal);
			}
			else tile.cellPos = Vector2D(CODE_BLOCK_SHEET_TEXT_SEGMENT, yVal);

			m_textureTiles.push_back(tile);
		}
	}

	// Create Parameter Sections //
	for (int i = 0; i < m_parameters; i++) 
	{
		MountPoint* point = new MountPoint();
		point->position = Vector2D((xVal + 1) * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE);
		point->contents = nullptr;
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

		if (m_conditionalBlock)
		{
			CreateTailEnd();
			CreateTail();
		}
	}
}

void CodeBlock::CreateTail()
{
	if (m_conditionalMountPoint->contents == nullptr) 
	{
		for (int i = 0; i < CODE_BLOCK_CONDITIONAL_TAIL_LENGTH; i++)
		{
			SpriteSheetTile tile;
			tile.renderOffset = Vector2D(0, (CODE_BLOCK_HEIGHT + i) * CODE_BLOCK_TILE_SIZE);

			tile.cellPos = Vector2D(CODE_BLOCK_SHEET_TAIL_SEGMENT);

			m_tailTextureTiles.push_back(tile);
		}
	}
	else 
	{
		Block* next = m_conditionalMountPoint->contents;
		int yVal = 0;
		int i = 0;
		while (next != nullptr) 
		{
			for (int j = 0; j < (CODE_BLOCK_HEIGHT - i % 2); j++)
			{
				SpriteSheetTile tile;
				tile.renderOffset = Vector2D(0,(CODE_BLOCK_HEIGHT + yVal) * CODE_BLOCK_TILE_SIZE);

				tile.cellPos = Vector2D(CODE_BLOCK_SHEET_TAIL_SEGMENT);

				m_tailTextureTiles.push_back(tile);
				yVal++;
			}
			next = next->GetNext();
			i++;
		}
	}
	m_endMountPoint->position = Vector2D(0, ((4 + m_tailTextureTiles.size()) * CODE_BLOCK_TILE_SIZE) - (CODE_BLOCK_TILE_SIZE / 2));
}

void CodeBlock::CreateTailEnd()
{
	for (int i = 0; i < m_size.x; i++) 
	{
		SpriteSheetTile tile;
		tile.renderOffset = Vector2D(i * CODE_BLOCK_TILE_SIZE, 0);

		tile.cellPos = Vector2D(2, CODE_BLOCK_SHEET_TAIL_END_Y);

		if (i == 0) tile.cellPos.x = 0;
		else if (i == 1) tile.cellPos.x = 1;
		else if (i == (m_size.x - 1)) tile.cellPos.x = 3;

		m_tailEndTextureTiles.push_back(tile);
	}
}

std::vector<MountPoint*>* CodeBlock::GetParameterMountPoints()
{
	return &m_paramPoints;
}
