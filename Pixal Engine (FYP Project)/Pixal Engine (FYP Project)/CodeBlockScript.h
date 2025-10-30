#pragma once
#include "CodeBlock.h"

class CodeBlockScript
{
private:
	std::vector<CodeBlock*> m_blocks;
	SDL_Renderer* m_renderer;
	bool playAudio = true;
	CodeBlock* selectedBlock = nullptr;
	Vector2D mouseDrag;
	float zoom = 1.f;

public:
	CodeBlockScript(SDL_Renderer* renderer);
	~CodeBlockScript();

	void Add(CodeBlock* block);

	void Update(float deltaTime, SDL_Event e);
	void Render();
};

