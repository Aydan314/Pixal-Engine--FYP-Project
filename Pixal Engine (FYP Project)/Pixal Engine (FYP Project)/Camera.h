#pragma once
#include "GameObject.h"
#include "Constants.h"

class Camera : GameObject
{
private:
	SDL_Color m_colour = { 0,0,0,0 };
	SDL_Color m_defaultColour = { 0,0,0,0 };

	float fadeTime = 0.f;
	int fadeDuration = 0;
	SDL_Color fadeColour = { 0,0,0,0 };

public:
	Camera(SDL_Renderer* renderer, SpriteSheetTexture ss_texture, GameObjectData gameObjectData);
	~Camera();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

	void FadeToColour(SDL_Color toColour, int duration);
	void UpdateFade(float deltaTime);

	bool FadeFinished();
};

