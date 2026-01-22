#include "GUIButton.h"

GUIButton::GUIButton(SDL_Renderer* renderer, Vector2D size, ButtonColours colours, GameObjectData gameObjectData) : GameObject(renderer, SpriteSheetTexture(), gameObjectData)
{
	m_bgColour = colours.defaultColour;
	m_colours = colours;
	m_size = size;

	Hitbox2D hitbox = Hitbox2D(&m_transform, size, { 0,0 }, m_renderer);
	m_hitboxes.push_back(hitbox);

	m_clicked = false;
}

GUIButton::~GUIButton()
{
}

void GUIButton::Render()
{
	// Draws a rectangle with the specified size and colour //

	SDL_Rect buttonRect;

	SDL_SetRenderDrawColor(m_renderer, m_bgColour.r, m_bgColour.g, m_bgColour.b, m_bgColour.a);

	buttonRect.x = m_transform.position.x;
	buttonRect.y = m_transform.position.y;
	buttonRect.w = m_size.x;
	buttonRect.h = m_size.y;

	SDL_RenderFillRect(m_renderer, &buttonRect);

	if (m_text != nullptr)
	{
		m_text->Render();
	}
}

void GUIButton::Update(float deltaTime, SDL_Event e)
{
	// Handles the various button states //
	if (m_selected)
	{
		// Detects interaction with the button //
		if (!m_clicked)
		{
			m_bgColour = m_colours.selectedColour;
			m_clicked = InputManager::Instance()->GetMouseLeftClicked();
		}
		else
		{
			m_bgColour = m_colours.clickedColour;
		}
	}
	else m_bgColour = m_colours.defaultColour;

	if (m_text != nullptr)
	{
		if (m_selected) m_text->SetColour(m_textSelectColour);
		else m_text->SetColour(m_textColour);
	}

}

bool GUIButton::GetClicked()
{
	return m_clicked;
}

void GUIButton::ResetClicked()
{
	m_clicked = false;
}

bool GUIButton::GetSelected()
{
	return m_selected;
}

void GUIButton::SetSelected(bool state)
{
	m_selected = state;
}

GUIText* GUIButton::GetText()
{
	return m_text;
}

void GUIButton::SetText(GUIText* text)
{
	m_text = text;
	m_text->CenterText({ m_transform.position.x + (m_size.x / 2.f),m_transform.position.y + (m_size.y / 2.f) });
	m_text->ReformatText();
	m_textColour = m_text->GetColour();

	m_textSelectColour = m_textColour;
	m_textSelectColour.a = m_textColour.a * 0.5f;
}

