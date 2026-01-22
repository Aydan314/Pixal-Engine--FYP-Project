#include "GUICanvas.h"

GUICanvas::GUICanvas(SDL_Renderer* renderer, Vector2D size, SDL_Color bgColour, GameObjectData gameObjectData) : GameObject(renderer, SpriteSheetTexture(), gameObjectData)
{
	m_size = size;
	m_bgColour = bgColour;
	selectedButton = 0;
}

GUICanvas::~GUICanvas()
{
	for (auto& item : m_buttons)
	{
		delete item;
	}
}

void GUICanvas::Render()
{
	// Renders a rectangle of the specified size and colour to the screen //

	SDL_Rect screenRect;

	SDL_SetRenderDrawColor(m_renderer, m_bgColour.r, m_bgColour.g, m_bgColour.b, m_bgColour.a);

	screenRect.x = m_transform.position.x;
	screenRect.y = m_transform.position.y;
	screenRect.w = m_size.x;
	screenRect.h = m_size.y;

	SDL_RenderFillRect(m_renderer, &screenRect);

	// Renders all the text objects on the canvas //
	for (auto& text : m_texts)
	{
		text->Render();
	}

	// Renders all the buttons on the canvas //

	for (auto& button : m_buttons)
	{
		button->Render();
	}
}

void GUICanvas::Update(float deltaTime, SDL_Event e)
{
	detectedInput = false;
	Vector2D mousePos = InputManager::Instance()->GetMousePos();

	if (m_visable)
	{
		// Handles the button selection //
		int i = 0;
		for (auto& button : m_buttons)
		{
			button->Update(deltaTime, e);

			if (((GameObject*)button)->GetHitboxes()[0].ContainsPoint(mousePos)) 
			{
				button->SetSelected(true);
				detectedInput = true;
			}
			else button->SetSelected(false);

			i++;
		}
	}
}

void GUICanvas::AddButton(GUIButton* button)
{
	m_buttons.push_back(button);
}

void GUICanvas::AddText(GameObject* text)
{
	m_texts.push_back(text);
}

void GUICanvas::SetDisableInput(bool state)
{
	disableInput = state;
}

bool GUICanvas::GetDetectedInput()
{
	return detectedInput;
}

std::vector<GUIButton*> GUICanvas::GetAttachedButtons()
{
	return m_buttons;
}

std::vector<GameObject*> GUICanvas::GetAttachedText()
{
	return m_texts;
}

void GUICanvas::ResetButtonSelected()
{
	selectedButton = 0;
}

