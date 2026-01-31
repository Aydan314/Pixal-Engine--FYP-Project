#pragma once
#include "GameObject.h"
#include "GUIButton.h"
#include "AudioManager.h"

class GUICanvas : public GameObject
{
private:
	SDL_Color m_bgColour = { 0,0,0,0 };
	Vector2D m_size = { 0,0 };
	std::vector<GUIButton*> m_buttons = {};
	std::vector<GameObject*> m_texts = {};
	signed int selectedButton = 0;
	bool disableInput = false;
	bool detectedInput = false;

public:
	GUICanvas(SDL_Renderer* renderer, Vector2D size, SDL_Color bgColour, GameObjectData gameObjectData);
	~GUICanvas();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

	void AddButton(GUIButton* button);
	void AddText(GameObject* text);
	void SetDisableInput(bool state);
	void SetBackgroundColour(SDL_Color colour);

	bool GetDetectedInput();
	std::vector<GUIButton*> GetAttachedButtons();
	std::vector<GameObject*> GetAttachedText();

	void ResetButtonSelected();
};


