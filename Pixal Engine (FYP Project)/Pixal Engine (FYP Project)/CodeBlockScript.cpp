#include "CodeBlockScript.h"

CodeBlockScript::CodeBlockScript(SDL_Renderer* renderer, GameScene* controlledScene)
{
	m_controlledScene = controlledScene;
	m_renderer = renderer;
	m_background = new Texture2D(renderer);
	m_background->LoadStoredTexture(ENGINE_BACKGROUND);

	m_start = new CodeBlock(m_renderer, { {ENGINE_SCREEN_WIDTH / 2,ENGINE_SCREEN_HEIGHT / 2},{0,0},0 }, controlledScene, BLOCK_ID_START);
	m_blocks.push_back(m_start);
}

CodeBlockScript::~CodeBlockScript()
{
}

void CodeBlockScript::Add(CodeBlock* block)
{
	m_blocks.push_back(block);
}

void CodeBlockScript::Add(CodeBlockParameter* parameter)
{
	m_blocks.push_back((CodeBlock*)parameter);
}

void CodeBlockScript::SetName(std::string name)
{
	m_name = name;
}

void CodeBlockScript::Update(float deltaTime, SDL_Event e)
{
	Vector2D zoomOffset = Vector2D(0, 0);

	if (InputManager::Instance()->IsKeyPressed(SDLK_F5) && InputManager::Instance()->Keystroke()) 
	{
		m_controlledScene->Clear();
		CodeBlockVariableManager::Instance()->Clear();
		m_start->Run();
		std::cout << "-----------------------\n";
	}

	if (InputManager::Instance()->GetMouseScroll() != 0) 
	{
		float zoomChange = InputManager::Instance()->GetMouseScroll() * ZOOM_SENSITIVITY;

		zoom += zoomChange;

		if (zoom > 0.f) zoomOffset = (Vector2D(ENGINE_SCREEN_WIDTH / -2.f, ENGINE_SCREEN_HEIGHT / -2.f)) * Vector2D(zoomChange, zoomChange);
		else zoom = zoom - zoomChange;
	}
	
	// Track mouse drag to move camera //
	mouseDrag = Vector2D(0, 0);
	if (InputManager::Instance()->GetMouseRightClicked()) mouseDrag = InputManager::Instance()->GetMouseMovement();

	// Update blocks and check if one is clicked on //
	for (Block* block : m_blocks) 
	{
		if (block->CheckMouseCollision() && InputManager::Instance()->GetMouseLeftClicked())
		{
			if (!selectedBlock || (block->GetType() == BLOCK_TYPE_PARAMETER && selectedBlock->GetType() != BLOCK_TYPE_PARAMETER))
			{
				selectedBlock = block;
				block->SetFocus(true);
			}
		}
		else if (InputManager::Instance()->GetMouseLeftClicked() || InputManager::Instance()->GetMouseRightClicked()) block->SetFocus(false);

		block->SetScale(Vector2D(zoom, zoom));
		block->SetPosition(zoomOffset + block->GetPosition() + (mouseDrag / Vector2D(zoom,zoom)));
		block->Update(deltaTime, e);
	}

	if (selectedBlock) 
	{
		// If block is selected, drag it around the screen //
		if (InputManager::Instance()->GetMouseLeftClicked() && !InputManager::Instance()->GetMouseRightClicked())
		{
			selectedBlock->GetHitboxes()[0]->SetColour({ 0,200,0,255 });
			selectedBlock->SetPosition(selectedBlock->GetPosition() + (InputManager::Instance()->GetMouseMovement() / Vector2D(zoom, zoom)));

			if (playAudio)
			{
				selectedBlock->SnapFrom();
				AudioManager::Instance()->PlayAudio("Engine Sounds/CodeBlockPickup.wav");
				playAudio = false;
			}
		}
		// If click is released snap to any nearby blocks //
		else 
		{
			if (playAudio == false)
			{
				AudioManager::Instance()->PlayAudio("Engine Sounds/CodeBlockPutdown.wav");
				playAudio = true;
			}

			for (Block* block : m_blocks) 
			{
				if (block != selectedBlock) 
				{
					bool selected = false;
					for (int i = 0; i < block->GetHitboxes().size(); i++) 
					{
						if (block->GetHitboxes()[i]->ContainsPoint(selectedBlock->GetPosition() + Vector2D(CODE_BLOCK_TILE_SIZE, 0)))
						{
							selectedBlock->SnapTo(block);
							selected = true;
							break;
						}
					}
					if (selected) break;
				}
			}

			selectedBlock->GetHitboxes()[0]->SetColour({ 200,0,0,255 });
			selectedBlock = nullptr;
		}
	}
}

void CodeBlockScript::Render()
{
	m_background->Render(Vector2D(0, 0), SDL_FLIP_NONE, 0, 0, 0, Vector2D(ENGINE_BACKGROUND_SCALE, ENGINE_BACKGROUND_SCALE));

	for (Block* block : m_blocks) 
	{
		block->Render();
	}

	for (CodeBlockParameter* param : m_params) 
	{
		param->Render();
	}
}

void CodeBlockScript::SelectBlock(Block* block)
{
	selectedBlock = block;
}

float CodeBlockScript::GetZoomValue()
{
	return zoom;
}

bool CodeBlockScript::IsBlockSelected()
{
	return selectedBlock != nullptr;
}

std::string CodeBlockScript::GetName()
{
	return m_name;
}
