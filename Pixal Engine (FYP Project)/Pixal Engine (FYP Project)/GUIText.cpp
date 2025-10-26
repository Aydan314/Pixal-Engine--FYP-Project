#include "GUIText.h"

GUIText::GUIText(SDL_Renderer* renderer, GameObjectData gameObjectData, TextData textData) : GameObject(renderer, SpriteSheetTexture(), gameObjectData)
{
	m_text = textData.text;
	m_fontPath = textData.fontPath;
	m_size = textData.size;
	m_colour = textData.colour;

	LoadFont(m_fontPath, m_size);
	ReformatText();
}

GUIText::~GUIText()
{
	TTF_CloseFont(m_font);

	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}

}

void GUIText::Render()
{
	SDL_RenderCopy(m_renderer, texture, NULL, &m_renderRect);
}

void GUIText::Update(float deltaTime, SDL_Event e)
{
}

void GUIText::ReformatText()
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
	m_renderRect = { (int)m_transform.position.x,(int)m_transform.position.y,w,h };
}

bool GUIText::LoadFont(std::string fontPath, unsigned int fontSize)
{
	m_font = TTF_OpenFont(fontPath.c_str(), fontSize);

	if (!m_font)
	{
		std::cout << "!! Could not load font from path " << fontPath << " Error: " << TTF_GetError() << " !!\n";
		return false;
	}

	return true;
}

void GUIText::SetColour(SDL_Color colour)
{
	m_colour = colour;
	ReformatText();
}

void GUIText::SetText(std::string text)
{
	m_text = text;
	ReformatText();
}

void GUIText::CenterText(Vector2D centerPos)
{
	m_transform.position.x = centerPos.x - (GetRenderRect().w / 2.f);
	m_transform.position.y = centerPos.y - (GetRenderRect().h / 2.f);
	ReformatText();
}

SDL_Color GUIText::GetColour()
{
	return m_colour;
}

std::string GUIText::GetText()
{
	return m_text;
}

SDL_Rect GUIText::GetRenderRect()
{
	return m_renderRect;
}
