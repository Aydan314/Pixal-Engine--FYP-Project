#pragma once
#include "GameObject.h"
#include "GUIText.h"
#include "FileHandler.h"

class GUITextBlock : GameObject
{
private:
	std::string m_text = "";
	std::string m_fontPath = "";
	SDL_Color m_colour = { 0,0,0,0 };
	int m_size = 0;
	Vector2D m_totalSize = { 0,0 };

	std::vector<GUIText*> m_textLines = {};

public:
	GUITextBlock(SDL_Renderer* renderer, GameObjectData gameObjectData, TextData textData);
	~GUITextBlock();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

	void SetColour(SDL_Color colour);
	void SetText(std::string text);
	void SetUpText();

	SDL_Color GetColour();
	std::string GetText();
	Rect2D GetRenderBox() { return Rect2D(m_transform.position.x, m_transform.position.y, m_totalSize.x, m_totalSize.y); }
};



