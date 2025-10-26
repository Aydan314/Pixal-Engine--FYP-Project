#pragma once
#include "GameObject.h"

class GUIText : GameObject
{
private:
	std::string m_text = "";
	std::string m_fontPath = "";
	unsigned int m_size = 0;
	TTF_Font* m_font = nullptr;
	SDL_Color m_colour = { 0,0,0 };
	SDL_Texture* texture = nullptr;
	SDL_Rect m_renderRect = { 0,0,0,0 };

public:
	GUIText(SDL_Renderer* renderer, GameObjectData gameObjectData, TextData textData);
	~GUIText();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;
	void ReformatText();

	bool LoadFont(std::string fontPath, unsigned int fontSize);

	void SetColour(SDL_Color colour);
	void SetText(std::string text);
	void CenterText(Vector2D centerPos);

	SDL_Color GetColour();
	std::string GetText();
	SDL_Rect GetRenderRect();

};

