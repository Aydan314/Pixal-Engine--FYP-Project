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

std::string InputManager::ReadTypedInput()
{
	std::string typed = typedInput;
	return typed;
}

void InputManager::ClearTypedInput()
{
	typedInput = "";
}

void InputManager::LoadTypedInputString(std::string text)
{
	typedInput = text;
}

bool InputManager::IsKeyPressed(SDL_Keycode key)
{
	return keyboard[key];
}

bool InputManager::Keystroke()
{
	return keyStroke;
}

void InputManager::Update(float deltaTime, SDL_Event e)
{
	// Update Mouse State //
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

	if (keyStroke) keyStroke = false;

	// Update Keyboard State //
	switch (e.type)
	{
	case SDL_KEYDOWN:
		keyboard[e.key.keysym.sym] = true;
		if (!keyDown) keyStroke = true;
		keyDown = true;
		switch (e.key.keysym.sym)
		{
		case SDLK_LSHIFT:
			shift = true;
			break;
		}

		break;
	case SDL_KEYUP:
		keyDown = false;
		if (keyboard[e.key.keysym.sym] == true) 
		{
			SDL_Keycode keystroke = e.key.keysym.sym;
			switch (keystroke) 
			{
			case SDLK_BACKSPACE:
				typedInput = typedInput.substr(0, typedInput.size() - 1);
				break;
			case SDLK_RETURN:
				break;
			case SDLK_CAPSLOCK:
				upperCase = !upperCase;
				break;
			case SDLK_LSHIFT:
				shift = false;
				break;
			default:
				typedInput += (char)keystroke - (std::abs(upperCase - shift) * CASE_DIFF);
				break;
			}
		}

		keyboard[e.key.keysym.sym] = false;
		break;
	}
}
