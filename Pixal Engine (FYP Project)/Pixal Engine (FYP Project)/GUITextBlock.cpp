#include "GUITextBlock.h"

GUITextBlock::GUITextBlock(SDL_Renderer* renderer, GameObjectData gameObjectData, TextData textData) : GameObject(renderer, SpriteSheetTexture(), gameObjectData)
{
	m_colour = textData.colour;
	m_text = textData.text;
	m_size = textData.size;
	m_fontPath = textData.fontPath;

	SetUpText();
}

GUITextBlock::~GUITextBlock()
{
	for (int i = 0; i < m_textLines.size(); i++)
	{
		delete m_textLines[i];
	}
}

void GUITextBlock::Render()
{
	// Renders each line of text //
	for (auto item : m_textLines)
	{
		item->Render();
	}
}

void GUITextBlock::Update(float deltaTime, SDL_Event e)
{
	// Updates each line of text //
	for (auto item : m_textLines)
	{
		item->Update(deltaTime, e);
	}
}

void GUITextBlock::SetColour(SDL_Color colour)
{
	m_colour = colour;
	SetUpText();
}

void GUITextBlock::SetText(std::string text)
{
	m_text = text;
	SetUpText();
}

void GUITextBlock::SetUpText()
{
	// creates a text object for each line  and calculates the maxiumum x and y it spans //
	for (int i = 0; i < m_textLines.size(); i++)
	{
		delete m_textLines[i];
	}

	m_textLines.clear();
	m_textLines.shrink_to_fit();
	m_totalSize = { 0,0 };

	std::vector<std::string> lines = FileHandler::Instance()->SplitData(m_text, "\n");

	int index = 0;
	for (auto& line : lines)
	{
		Transform transform = { Vector2D(m_transform.position.x,m_transform.position.y + (m_size * index)), Vector2D(1.f,1.f),0 };

		GUIText* newText = new GUIText(m_renderer, { transform, COLLISION_NONE }, TextData{ line,m_fontPath,m_size,m_colour });

		if (newText->GetRenderRect().w > m_totalSize.x) m_totalSize.x = newText->GetRenderRect().w;
		if (newText->GetRenderRect().h > m_totalSize.y) m_totalSize.y = newText->GetRenderRect().h;


		m_textLines.push_back(newText);
		index++;
	}

}

SDL_Color GUITextBlock::GetColour()
{
	return m_colour;
}

std::string GUITextBlock::GetText()
{
	return m_text;
}
