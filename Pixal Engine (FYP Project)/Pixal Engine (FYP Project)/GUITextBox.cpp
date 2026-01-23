#include "GUITextBox.h"

GUITextBox::GUITextBox(SDL_Renderer* renderer, Vector2D size, GameObjectData gameObjectData, TextData textData) : GameObject(renderer, SpriteSheetTexture(), gameObjectData)
{
	m_size = size;
	m_text = textData.text;
	m_fontPath = textData.fontPath;
	m_fontSize = textData.size;
	m_colour = textData.colour;

	Hitbox2D hitbox = Hitbox2D(&m_transform, m_size);
	m_hitboxes.push_back(hitbox);

	LoadFont(m_fontPath, m_fontSize);
	ReformatText();
}

GUITextBox::~GUITextBox()
{
	TTF_CloseFont(m_font);

	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}

}

void GUITextBox::Render()
{
	SDL_RenderCopy(m_renderer, texture, NULL, &m_renderRect);
}

void GUITextBox::Update(float deltaTime, SDL_Event e)
{
	if (m_focus)
	{
		if (!m_LastFocus) InputManager::Instance()->LoadTypedInputString(m_text);
		m_text = InputManager::Instance()->ReadTypedInput();

		ReformatText();
	}
	else if (m_LastFocus) InputManager::Instance()->ClearTypedInput();

	m_LastFocus = m_focus;
}

void GUITextBox::ReformatText()
{
	// Destroy texture to avoid memory leak //
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}

	// Size the text //
	int w, h;
	TTF_SizeText(m_font, m_text.c_str(), &w, &h);

	// Load surface and texture //
	SDL_Surface* surf = TTF_RenderText_Blended(m_font, m_text.c_str(), m_colour);
	texture = SDL_CreateTextureFromSurface(m_renderer, surf);
	SDL_FreeSurface(surf);

	// Get render rect and render with it //
	m_renderRect =
	{
		(int)round(m_transform.position.x * m_transform.scale.x),
		(int)round(m_transform.position.y * m_transform.scale.y),
		(int)round(w * m_transform.scale.x),
		(int)round(h * m_transform.scale.y)
	};
}

bool GUITextBox::LoadFont(std::string fontPath, unsigned int fontSize)
{
	m_font = TTF_OpenFont(fontPath.c_str(), fontSize);

	if (!m_font)
	{
		std::cout << "!! Could not load font from path " << fontPath << " Error: " << TTF_GetError() << " !!\n";
		return false;
	}

	return true;
}

void GUITextBox::SetColour(SDL_Color colour)
{
	m_colour = colour;
	ReformatText();
}

void GUITextBox::SetText(std::string text)
{
	m_text = text;
	ReformatText();
}

void GUITextBox::CenterText(Vector2D centerPos)
{
	m_transform.position.x = centerPos.x - (GetRenderRect().w / 2.f);
	m_transform.position.y = centerPos.y - (GetRenderRect().h / 2.f);
	ReformatText();
}

void GUITextBox::SetFocus(bool focus)
{
	m_focus = focus;
}

SDL_Color GUITextBox::GetColour()
{
	return m_colour;
}

std::string GUITextBox::GetText()
{
	return m_text;
}

SDL_Rect GUITextBox::GetRenderRect()
{
	return m_renderRect;
}
