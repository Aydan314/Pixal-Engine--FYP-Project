#include "CodeBlockScript.h"

CodeBlockScript::CodeBlockScript(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

CodeBlockScript::~CodeBlockScript()
{
}

void CodeBlockScript::Add(CodeBlock* block)
{
	m_blocks.push_back(block);
}

void CodeBlockScript::Update(float deltaTime, SDL_Event e)
{
	Vector2D zoomOffset = Vector2D(0, 0);

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
	for (CodeBlock* block : m_blocks) 
	{
		if 
		(block->CheckMouseCollision() && !selectedBlock && InputManager::Instance()->GetMouseLeftClicked())
		{
			selectedBlock = block;
		}

		block->SetScale(Vector2D(zoom, zoom));
		block->SetPosition(zoomOffset + block->GetPosition() + (mouseDrag / Vector2D(zoom,zoom)));
		block->Update(deltaTime, e);
	}

	if (selectedBlock) 
	{
		// If block is selected, drag it around the screen //
		if (InputManager::Instance()->GetMouseLeftClicked() && !InputManager::Instance()->GetMouseRightClicked())
		{
			selectedBlock->GetHitboxes()->at(0).SetColour({ 0,200,0,255 });
			selectedBlock->SetPosition(selectedBlock->GetPosition() + (InputManager::Instance()->GetMouseMovement() / Vector2D(zoom, zoom)));

			if (playAudio)
			{
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

			for (CodeBlock* block : m_blocks) 
			{
				if (block != selectedBlock) 
				{
					if (block->GetHitboxes()->at(0).ContainsPoint(selectedBlock->GetPosition() + Vector2D(CODE_BLOCK_TILE_SIZE,0))) 
					{
						selectedBlock->SnapTo(block);
						break;
					}
				}
			}

			selectedBlock->GetHitboxes()->at(0).SetColour({ 200,0,0,255 });
			selectedBlock = nullptr;
		}
	}
}

void CodeBlockScript::Render()
{
	for (CodeBlock* block : m_blocks) 
	{
		block->Render();
	}
}
