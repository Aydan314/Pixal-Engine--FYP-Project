#pragma once
#include "GameObject.h"
#include "GUIText.h"
#include "AudioManager.h"

class GUIButton : GameObject
{
private:
	SDL_Color m_bgColour = { 0,0,0,0 };
	SDL_Color m_textColour = { 0,0,0,0 };
	SDL_Color m_textSelectColour = { 0,0,0,0 };
	ButtonColours m_colours = ButtonColours();
	Vector2D m_size = { 0.f,0.f };
	GUIText* m_text = nullptr;

	bool m_clicked = false;
	bool m_selected = false;

public:
	GUIButton(SDL_Renderer* renderer, Vector2D size, ButtonColours colours, GameObjectData gameObjectData);
	~GUIButton();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

	bool GetClicked();
	void ResetClicked();

	bool GetSelected();
	void SetSelected(bool state);

	GUIText* GetText();
	void SetText(GUIText* text);
};