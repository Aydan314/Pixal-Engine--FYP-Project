#pragma once
#include "CodeBlock.h"
#include "CodeBlockParameter.h"

class CodeBlockScript
{
private:
	std::vector<CodeBlock*> m_blocks;
	std::vector<CodeBlockParameter*> m_params;
	std::string m_name = "Script";
	SDL_Renderer* m_renderer;
	Texture2D* m_background;
	bool playAudio = true;
	CodeBlock* selectedBlock = nullptr;
	Vector2D mouseDrag;
	float zoom = 1.f;

public:
	CodeBlockScript(SDL_Renderer* renderer);
	~CodeBlockScript();

	void Add(CodeBlock* block);
	void Add(CodeBlockParameter* parameter);
	void SetName(std::string name);

	void Update(float deltaTime, SDL_Event e);
	void Render();

	std::string GetName();
};

