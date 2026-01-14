#pragma once
#include "Block.h"

class CodeBlock : public Block
{
protected:
	Vector2D m_textArea;

	GUIText* m_text;
	int m_parameters;
	std::vector<SpriteSheetTile> m_tailTextureTiles;
	std::vector<SpriteSheetTile> m_tailEndTextureTiles;
	

public:
	CodeBlock(SDL_Renderer* renderer, Transform transform, BLOCK_ID ID = BLOCK_ID_CUSTOM);
	~CodeBlock();

	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;
	void Resize() override;

	void CreateBlockOfSize(Vector2D size) override;
	void CreateTail();
	void CreateTailEnd();
	void Init(BLOCK_ID ID);

	std::vector<MountPoint*>* GetParameterMountPoints();
	
};

