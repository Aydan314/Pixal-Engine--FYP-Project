#pragma once
#include "CodeBlock.h"
#include "CodeBlockParameter.h"
#include "Block.h"

class CodeBlockScript
{
private:
	std::vector<Block*> m_blocks;
	std::vector<CodeBlockParameter*> m_params;
	std::string m_name = "Script";
	GameObject* m_controlledObject = nullptr;
	CodeBlock* m_start = nullptr;

	SDL_Renderer* m_renderer;
	Texture2D* m_background;

	bool playAudio = true;
	Block* selectedBlock = nullptr;
	Vector2D mouseDrag;
	float zoom = 1.f;

public:
	CodeBlockScript(SDL_Renderer* renderer, GameObject* controlledObject = nullptr);
	~CodeBlockScript();

	void Add(CodeBlock* block);
	void Add(CodeBlockParameter* parameter);
	void SetName(std::string name);

	void Update(float deltaTime, SDL_Event e);
	void Render();
	void SelectBlock(Block* block);
	
	float GetZoomValue();
	bool IsBlockSelected();
	std::string GetName();
};

