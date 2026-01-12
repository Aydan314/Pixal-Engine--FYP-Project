#pragma once
#include "Block.h"

class CodeBlock : public Block
{
protected:
	Vector2D m_textArea;

	GUIText* m_text;
	int m_parameters;
	

public:
	CodeBlock(SDL_Renderer* renderer, Transform transform);
	~CodeBlock();

	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

	void CreateBlockOfSize(Vector2D size) override;

	std::vector<MountPoint*>* GetParameterMountPoints();
	
};

