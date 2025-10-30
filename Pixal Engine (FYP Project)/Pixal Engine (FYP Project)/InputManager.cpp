#include "InputManager.h"
InputManager* InputManager::m_instance;

InputManager::InputManager()
{
	mouseX = 0;
	mouseY = 0;
	prevMouseX = 0;
	prevMouseY = 0;
}

InputManager::~InputManager()
{
}

Vector2D InputManager::GetMousePos()
{
	
	return Vector2D(mouseX, mouseY);
}

Vector2D InputManager::GetMouseMovement()
{
	return Vector2D(mouseX - prevMouseX, mouseY - prevMouseY);
}

bool InputManager::GetMouseLeftClicked()
{
	return mouseLeftClick;
}

bool InputManager::GetMouseRightClicked()
{
	return mouseRightClick;
}

int InputManager::GetMouseScroll()
{
	return mouseScroll;
}

void InputManager::Update(float deltaTime, SDL_Event e)
{
	prevMouseX = mouseX; prevMouseY = mouseY;
	mouseScroll = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	switch (e.type) 
	{
	case SDL_MOUSEBUTTONDOWN:
		{
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseLeftClick = true;
				break;
			case SDL_BUTTON_RIGHT:
				mouseRightClick = true;
				break;
			default:
				break;
			}
		}
		break;

	case SDL_MOUSEBUTTONUP:
		{
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseLeftClick = false;
				break;
			case SDL_BUTTON_RIGHT:
				mouseRightClick = false;
				break;
			default:
				break;
			}
		}
		break;

	case SDL_MOUSEWHEEL:
		switch (e.wheel.type)
		{
		case SDL_MOUSEWHEEL:
			
			mouseScroll = e.wheel.y;
			break;
		}

	default:
		break;
	}
	
}
