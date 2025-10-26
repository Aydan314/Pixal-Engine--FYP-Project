#include "Camera.h"

Camera::Camera(SDL_Renderer* renderer, SpriteSheetTexture ss_texture, GameObjectData gameObjectData) : GameObject(renderer, ss_texture, gameObjectData)
{
	m_defaultColour = { 0,0,0,0 };
	m_colour = m_defaultColour;
}

Camera::~Camera()
{
}

void Camera::Render()
{
	// Draws a tint across the whole screen //
	SDL_Rect screenRect;

	SDL_SetRenderDrawColor(m_renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);

	screenRect.x = 0;
	screenRect.y = 0;
	screenRect.w = GAME_SCREEN_WIDTH;
	screenRect.h = GAME_SCREEN_HEIGHT;

	SDL_RenderFillRect(m_renderer, &screenRect);
}

void Camera::Update(float deltaTime, SDL_Event e)
{
	if (fadeDuration != 0) UpdateFade(deltaTime);
}

void Camera::FadeToColour(SDL_Color toColour, int duration)
{
	fadeDuration = duration;
	fadeColour = toColour;
}

void Camera::UpdateFade(float deltaTime)
{

	fadeTime += deltaTime * 1000.f;

	if (fadeTime < fadeDuration)
	{
		// Fades the opacity of the new colour via a sine wave //
		SDL_Color newColour = { 0,0,0,0 };

		newColour.r = m_defaultColour.r + (Uint8)(fadeColour.r * sinf((fadeTime / (float)fadeDuration) * 3.14159f));
		newColour.g = m_defaultColour.g + (Uint8)(fadeColour.g * sinf((fadeTime / (float)fadeDuration) * 3.14159f));
		newColour.b = m_defaultColour.b + (Uint8)(fadeColour.b * sinf((fadeTime / (float)fadeDuration) * 3.14159f));
		newColour.a = m_defaultColour.a + (Uint8)(fadeColour.a * sinf((fadeTime / (float)fadeDuration) * 3.14159f));

		m_colour = newColour;
	}
	else
	{
		// Resets the tint to the origional colour //
		fadeTime = 0;
		fadeDuration = 0;
		m_colour = m_defaultColour;
	}
}

bool Camera::FadeFinished()
{
	return fadeDuration == 0;
}
