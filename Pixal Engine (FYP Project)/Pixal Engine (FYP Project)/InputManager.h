#pragma once
#include <iostream>
#include "Vector2D.h"
#include "SDL.h"
#include <map>

#define CASE_DIFF 32

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
	std::string typedInput;
	bool upperCase = false;
	bool shift = false;

	bool keyDown = false;
	bool keyStroke = false;
	
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
	std::string ReadTypedInput();
	void LoadTypedInputString(std::string text);
	void ClearTypedInput();


	bool IsKeyPressed(SDL_Keycode key);
	bool Keystroke();

	void Update(float deltaTime, SDL_Event e);
};

