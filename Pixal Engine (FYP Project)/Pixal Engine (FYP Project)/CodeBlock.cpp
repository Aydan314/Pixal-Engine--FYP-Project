#include "CodeBlock.h"

CodeBlock::CodeBlock(SDL_Renderer* renderer, Transform transform, GameScene* gameScene, BLOCK_ID ID) : Block(renderer, transform, gameScene)
{
	m_type = BLOCK_TYPE_BLOCK;
	m_ID = ID;
	m_renderer = renderer;
	m_transform = transform;

	Init(ID);
	CreateBlock();
	InitMountPoints();

	if (m_conditionalBlock)
	{
		CreateTailEnd();
		CreateTail();
	}
}

CodeBlock::~CodeBlock()
{
}

void CodeBlock::Init(BLOCK_ID ID)
{
	m_parameters = 0;

	switch (ID) 
	{

	case BLOCK_ID_SET_POSITION:
		m_name = "Set Position Of           to X=        Y=";
		m_colour = COLOUR_GREEN;
		m_template =
		{
			{BlockSectionStart},{BlockSectionSpace,5},{BlockSectionParameter},{BlockSectionSpace,2},{BlockSectionParameter},{BlockSectionSpace,1},{BlockSectionParameter},{BlockSectionEnd}
		};
		break;

	case BLOCK_ID_SET_VELOCITY:
		m_name = "Set Velocity Of           to X=        Y=";
		m_colour = COLOUR_GREEN;
		m_template =
		{
			{BlockSectionStart},{BlockSectionSpace,5},{BlockSectionParameter},{BlockSectionSpace,2},{BlockSectionParameter},{BlockSectionSpace,1},{BlockSectionParameter},{BlockSectionEnd}
		};
		break;

	case BLOCK_ID_IF:
		m_name = "If                =";
		m_colour = COLOUR_LIGHT_GREY;
		m_template =
		{
			{BlockSectionConditionalStart},{BlockSectionSpace,1},{BlockSectionParameter},{BlockSectionSpace,1},{BlockSectionParameter},{ BlockSectionEnd }
		};
		break;

	case BLOCK_ID_STOP:
		m_name = "Stop";
		m_colour = COLOUR_RED;
		m_template =
		{
			{BlockSectionEndingStart},{BlockSectionSpace,3},{BlockSectionEnd}
		};
		break;

	case BLOCK_ID_START:
		m_name = "On Start";
		m_colour = COLOUR_GREEN;
		m_template =
		{
			{BlockSectionBeginningStart},{BlockSectionSpace,3},{BlockSectionEnd}
		};
		break;

	case BLOCK_ID_CREATE_GAMEOBJECT:
		m_name = "Create GameObject Called";
		m_colour = COLOUR_GREEN;
		m_template =
		{
			{BlockSectionStart},{BlockSectionSpace,8},{BlockSectionParameter},{BlockSectionEnd}
		};
		break;

	case BLOCK_ID_ON_KEY:
		m_name = "On Key";
		m_colour = COLOUR_ORANGE;
		m_template =
		{
			{BlockSectionBeginningStart},{BlockSectionSpace,2},{BlockSectionParameter},{ BlockSectionEnd }
		};
		break;

	default:
		m_name = "CODE BLOCK";
		m_colour = COLOUR_WHITE;
		m_template =
		{
			{BlockSectionStart},{BlockSectionSpace,3},{BlockSectionEnd}
		};
		break;
	}

	m_text = new GUIText(m_renderer, GameObjectData{ m_transform,COLLISION_NONE }, TextData{ m_name,ENGINE_FONT_PATH,30,{255,255,255,255} });
}

void CodeBlock::InitMountPoints()
{
	m_startMountPoint = new MountPoint();
	m_startMountPoint->type = MOUNT_TYPE_START;

	m_conditionalMountPoint = nullptr;
	if (m_conditionalBlock)
	{
		m_conditionalMountPoint = new MountPoint();
		m_conditionalMountPoint->position = Vector2D(CODE_BLOCK_TILE_SIZE, (CODE_BLOCK_HEIGHT * CODE_BLOCK_TILE_SIZE) - (CODE_BLOCK_TILE_SIZE / 2));
		m_conditionalMountPoint->type = MOUNT_TYPE_CONDITIONAL;
	}

	m_endMountPoint = new MountPoint();
	m_endMountPoint->contents = nullptr;
	m_endMountPoint->position = Vector2D(0, (CODE_BLOCK_HEIGHT * CODE_BLOCK_TILE_SIZE) - (CODE_BLOCK_TILE_SIZE / 2));
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
	((GameObject*)m_text)->SetPosition(m_transform.position + Vector2D(CODE_BLOCK_TILE_SIZE / 2.f, ((CODE_BLOCK_HEIGHT * CODE_BLOCK_TILE_SIZE) - (m_text->GetRenderRect().h / m_transform.scale.y))/ 2.f) );
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
	GameObject* newObject = nullptr;
	DataContent content;

	switch (m_ID) 
	{
	case BLOCK_ID_SET_POSITION:
		if (m_paramPoints[0]->contents)
		{
			float X = 0;
			float Y = 0;

			if (m_paramPoints[1]->contents) X = ((CodeBlockParameter*)m_paramPoints[1]->contents)->GetContents().number;
			if (m_paramPoints[2]->contents) Y = ((CodeBlockParameter*)m_paramPoints[2]->contents)->GetContents().number;

			std::string varName = ((CodeBlockParameter*)m_paramPoints[0]->contents)->GetContents().name;
			CodeBlockVariableManager::Instance()->GetVariable(varName).gameObject->SetPosition(Vector2D(X, Y));
			std::cout << "Set position of " << varName << " to " << X << "," << Y << "\n";
		}
		break;

	case BLOCK_ID_CREATE_GAMEOBJECT:
		if (m_paramPoints[0]->contents)
		{
			newObject = new GameObject
			(
				m_gameScene->GetRenderer(),
				SpriteSheetTexture{ "Engine Images/Sprites.png", {2,2},{0,0} },
				GameObjectData{ Transform{ {0,0},{1,1},0 },COLLISION_SINGLE }
			);
			m_gameScene->Add(newObject);

			content.gameObject = newObject;

			std::string varName = ((CodeBlockParameter*)m_paramPoints[0]->contents)->GetContents().name;
			CodeBlockVariableManager::Instance()->SetVariable(varName, content);
			std::cout << "Create new object called: " << varName << "\n";
		}
		break;

	case BLOCK_ID_SET_VELOCITY:
		if (m_paramPoints[0]->contents)
		{
			float X = 0;
			float Y = 0;

			if (m_paramPoints[1]->contents) X = ((CodeBlockParameter*)m_paramPoints[1]->contents)->GetContents().number;
			if (m_paramPoints[2]->contents) Y = ((CodeBlockParameter*)m_paramPoints[2]->contents)->GetContents().number;

			std::string varName = ((CodeBlockParameter*)m_paramPoints[0]->contents)->GetContents().name;
			CodeBlockVariableManager::Instance()->GetVariable(varName).gameObject->SetVelocity(Vector2D(X, Y));
			std::cout << "Set Velocity of " << varName << " to " << X << "," << Y << "\n";
		}
		break;

	case BLOCK_ID_ON_KEY:
		m_condition = false;
		if (m_paramPoints[0]->contents) 
		{
			std::string key = ((CodeBlockParameter*)m_paramPoints[0]->contents)->GetContents().string;
			SDL_KeyCode keyPress = (SDL_KeyCode)key[0];
			m_condition = InputManager::Instance()->IsKeyPressed(keyPress);
		}
		break;

	default:
		std::cout << m_name << "\n";
		break;
	}
	
	if (GetNext() && m_condition) GetNext()->Run();
}

void CodeBlock::CreateBlock()
{
	m_paramPoints.clear();

	int index = 0;
	for (BlockSection section : m_template) 
	{
		switch (section.type) 
		{
		case BlockSectionStart:
			CreateStartSegment(&index);
			break;

		case BlockSectionConditionalStart:
			CreateConditionalStartSegment(&index);
			break;

		case BlockSectionBeginningStart:
			CreateBeginningStartSegment(&index);
			break;

		case BlockSectionEndingStart:
			CreateEndingStartSegment(&index);
			break;

		case BlockSectionSpace:
			CreateSpaceSegment(&index, section.size);
			break;

		case BlockSectionParameter:
			CreateParameterSegment(&index);
			break;

		case BlockSectionEnd:
			CreateEndSegment(&index);
			break;
		}
	}
	m_size = index;

	Hitbox2D* hitbox = new Hitbox2D(&m_transform, Vector2D(m_size * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_HEIGHT * CODE_BLOCK_TILE_SIZE), Vector2D(0, 0), m_renderer);
	m_hitboxes.push_back(hitbox);
}

BLOCK_ID CodeBlock::GetID()
{
	return m_ID;
}

void CodeBlock::CreateStartSegment(int* index)
{
	int segmentSize = 2;

	std::vector<Vector2D> sliceCells
	{
		{CODE_BLOCK_START_SEGMENT,0},
		{CODE_BLOCK_START_SEGMENT,1},
		{CODE_BLOCK_START_SEGMENT,2},

		{CODE_BLOCK_START_SEGMENT + 1, 0},
		{CODE_BLOCK_START_SEGMENT + 1, 1},
		{CODE_BLOCK_START_SEGMENT + 1, 2}
	};

	std::vector<Vector2D> slicePositions
	{
		{0,0},
		{0,1},
		{0,2},

		{1,0},
		{1,1},
		{1,2}
	};

	for (int i = 0; i < sliceCells.size(); i++) 
	{
		SpriteSheetTile tile;
		tile.renderOffset = slicePositions[i] * CODE_BLOCK_TILE_SIZE;
		tile.cellPos = sliceCells[i];

		m_textureTiles.push_back(tile);
	}

	*index += segmentSize;
}

void CodeBlock::CreateConditionalStartSegment(int* index)
{
	int segmentSize = 3;
	m_conditionalBlock = true;

	std::vector<Vector2D> sliceCells
	{
		{CODE_BLOCK_START_SEGMENT,0},
		{CODE_BLOCK_START_SEGMENT,1},
		{CODE_BLOCK_START_SEGMENT,CODE_BLOCK_CONDITIONAL_SEGMENT},

		{CODE_BLOCK_START_SEGMENT + 1, 0},
		{CODE_BLOCK_START_SEGMENT + 1, 1},
		{CODE_BLOCK_BLANK_SEGMENT, 2},

		{CODE_BLOCK_BLANK_SEGMENT,0},
		{CODE_BLOCK_BLANK_SEGMENT,1},
		{CODE_BLOCK_START_SEGMENT + 1,2}
	};

	std::vector<Vector2D> slicePositions
	{
		{0,0},
		{0,1},
		{0,2},

		{1,0},
		{1,1},
		{1,2},

		{2,0},
		{2,1},
		{2,2}
	};

	for (int i = 0; i < sliceCells.size(); i++)
	{
		SpriteSheetTile tile;
		tile.renderOffset = slicePositions[i] * CODE_BLOCK_TILE_SIZE;
		tile.cellPos = sliceCells[i];

		m_textureTiles.push_back(tile);
	}

	*index += segmentSize;
}

void CodeBlock::CreateBeginningStartSegment(int* index)
{
	int segmentSize = 2;
	m_startBlock = true;

	std::vector<Vector2D> sliceCells
	{
		{CODE_BLOCK_START_SEGMENT,0},
		{CODE_BLOCK_START_SEGMENT,1},
		{CODE_BLOCK_START_SEGMENT,2},

		{CODE_BLOCK_BLANK_SEGMENT, 0},
		{CODE_BLOCK_START_SEGMENT + 1, 1},
		{CODE_BLOCK_START_SEGMENT + 1, 2}
	};

	std::vector<Vector2D> slicePositions
	{
		{0,0},
		{0,1},
		{0,2},

		{1,0},
		{1,1},
		{1,2}
	};

	for (int i = 0; i < sliceCells.size(); i++)
	{
		SpriteSheetTile tile;
		tile.renderOffset = slicePositions[i] * CODE_BLOCK_TILE_SIZE;
		tile.cellPos = sliceCells[i];

		m_textureTiles.push_back(tile);
	}

	*index += segmentSize;
}

void CodeBlock::CreateEndingStartSegment(int* index)
{
	int segmentSize = 2;
	m_endBlock = true;

	std::vector<Vector2D> sliceCells
	{
		{CODE_BLOCK_START_SEGMENT,0},
		{CODE_BLOCK_START_SEGMENT,1},
		{CODE_BLOCK_START_SEGMENT,2},

		{CODE_BLOCK_START_SEGMENT + 1, 0},
		{CODE_BLOCK_START_SEGMENT + 1, 1},
		{CODE_BLOCK_BLANK_SEGMENT, 2}
	};

	std::vector<Vector2D> slicePositions
	{
		{0,0},
		{0,1},
		{0,2},

		{1,0},
		{1,1},
		{1,2}
	};

	for (int i = 0; i < sliceCells.size(); i++)
	{
		SpriteSheetTile tile;
		tile.renderOffset = slicePositions[i] * CODE_BLOCK_TILE_SIZE;
		tile.cellPos = sliceCells[i];

		m_textureTiles.push_back(tile);
	}

	*index += segmentSize;
}

void CodeBlock::CreateSpaceSegment(int* index, int size)
{
	int segmentSize = size;

	std::vector<Vector2D> sliceCells =
	{
		{CODE_BLOCK_BLANK_SEGMENT,0},
		{CODE_BLOCK_BLANK_SEGMENT,1},
		{CODE_BLOCK_BLANK_SEGMENT,2}
	};

	std::vector<Vector2D> slicePositions
	{
		{0,0},
		{0,1},
		{0,2}
	};

	for (int i = 0; i < segmentSize; i++) 
	{
		for (int j = 0; j < sliceCells.size(); j++) 
		{
			SpriteSheetTile tile;
			tile.renderOffset = (slicePositions[j] + Vector2D(*index, 0) + Vector2D(i, 0)) * CODE_BLOCK_TILE_SIZE;
			tile.cellPos = sliceCells[j];

			m_textureTiles.push_back(tile);
		}
	}
	*index += segmentSize;
}

void CodeBlock::CreateParameterSegment(int* index)
{
	int segmentSize = 3;

	MountPoint* param = new MountPoint();
	param->contents = nullptr;
	param->position = Vector2D(*index * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE);

	m_parameters++;

	m_paramPoints.push_back(param);

	std::vector<Vector2D> sliceCells
	{
		{CODE_BLOCK_PARAMETER_SEGMENT,0},
		{CODE_BLOCK_PARAMETER_SEGMENT,1},
		{CODE_BLOCK_PARAMETER_SEGMENT,2},

		{CODE_BLOCK_PARAMETER_SEGMENT + 1, 0},
		{CODE_BLOCK_PARAMETER_SEGMENT + 1, 1},
		{CODE_BLOCK_PARAMETER_SEGMENT + 1, 2},

		{CODE_BLOCK_PARAMETER_SEGMENT + 2, 0},
		{CODE_BLOCK_PARAMETER_SEGMENT + 2, 1},
		{CODE_BLOCK_PARAMETER_SEGMENT + 2, 2}
	};

	std::vector<Vector2D> slicePositions
	{
		{0,0},
		{0,1},
		{0,2},

		{1,0},
		{1,1},
		{1,2},

		{2,0},
		{2,1},
		{2,2}
	};

	for (int i = 0; i < sliceCells.size(); i++)
	{
		SpriteSheetTile tile;
		tile.renderOffset = (slicePositions[i] + Vector2D(*index, 0) ) * CODE_BLOCK_TILE_SIZE;
		tile.cellPos = sliceCells[i];

		m_textureTiles.push_back(tile);
	}

	*index += segmentSize;
}

void CodeBlock::CreateEndSegment(int* index)
{
	int segmentSize = 1;

	std::vector<Vector2D> sliceCells =
	{
		{CODE_BLOCK_END_SEGMENT,0},
		{CODE_BLOCK_END_SEGMENT,1},
		{CODE_BLOCK_END_SEGMENT,2}
	};

	std::vector<Vector2D> slicePositions
	{
		{0,0},
		{0,1},
		{0,2}
	};


	for (int i = 0; i < sliceCells.size(); i++)
	{
		SpriteSheetTile tile;
		tile.renderOffset = (slicePositions[i] + Vector2D(*index, 0)) * CODE_BLOCK_TILE_SIZE;
		tile.cellPos = sliceCells[i];

		m_textureTiles.push_back(tile);
	}

	*index += segmentSize;
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
	m_endHitbox = new Hitbox2D
	(
		&m_transform,
		Vector2D(m_size * CODE_BLOCK_TILE_SIZE, CODE_BLOCK_TILE_SIZE),
		Vector2D(0, (CODE_BLOCK_HEIGHT + CODE_BLOCK_CONDITIONAL_TAIL_LENGTH + 1) * CODE_BLOCK_TILE_SIZE),
		m_renderer
	);

	m_hitboxes.push_back(m_endHitbox);

	for (int i = 0; i < m_size; i++) 
	{
		SpriteSheetTile tile;
		tile.renderOffset = Vector2D(i * CODE_BLOCK_TILE_SIZE, 0);

		tile.cellPos = Vector2D(2, CODE_BLOCK_SHEET_TAIL_END_Y);

		if (i == 0) tile.cellPos.x = 0;
		else if (i == 1) tile.cellPos.x = 1;
		else if (i == (m_size - 1)) tile.cellPos.x = 3;

		m_tailEndTextureTiles.push_back(tile);
	}
}

std::vector<MountPoint*>* CodeBlock::GetParameterMountPoints()
{
	return &m_paramPoints;
}
