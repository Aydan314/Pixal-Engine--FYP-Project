#pragma once
#include <iostream>
#include "Vector2D.h"
#include "SDL.h"
#include <map>

class InputManager
{
private:
	InputManager();
	
	static InputManager* m_instance;

	int prevMouseX;
	int prevMouseY;

	int mouseX;
	int mouseY;

	int mouseScroll = 0;

	bool mouseLeftClick = false;
	bool mouseRightClick = false;

	std::map<int, bool> keyboard;
	
public:
	static inline InputManager* Instance() {
		if (!m_instance)
		{
			m_instance = new InputManager();
		}
		return m_instance;
	}

	~InputManager();

	Vector2D GetMousePos();
	Vector2D GetMouseMovement();
	bool GetMouseLeftClicked();
	bool GetMouseRightClicked();
	int GetMouseScroll();

	bool IsKeyPressed(SDL_Keycode key);

	void Update(float deltaTime, SDL_Event e);
};

