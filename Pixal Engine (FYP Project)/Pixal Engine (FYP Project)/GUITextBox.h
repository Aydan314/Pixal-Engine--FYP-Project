#pragma once
#include "GameObject.h"

class GUITextBox : GameObject
{
private:
	std::string m_text = "";
	std::string m_fontPath = "";
	unsigned int m_fontSize = 0;
	Vector2D m_size = { 1,1 };
	TTF_Font* m_font = nullptr;
	SDL_Color m_colour = { 0,0,0 };
	SDL_Texture* texture = nullptr;
	SDL_Rect m_renderRect = { 0,0,0,0 };
	bool m_focus = false;
	bool m_LastFocus = m_focus;

public:
	GUITextBox(SDL_Renderer* renderer, Vector2D size, GameObjectData gameObjectData, TextData textData);
	~GUITextBox();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;
	void ReformatText();

	bool LoadFont(std::string fontPath, unsigned int fontSize);

	void SetColour(SDL_Color colour);
	void SetText(std::string text);
	void CenterText(Vector2D centerPos);
	void SetFocus(bool focus);

	SDL_Color GetColour();
	std::string GetText();
	SDL_Rect GetRenderRect();

};

