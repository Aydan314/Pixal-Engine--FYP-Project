#pragma once
#include "Block.h"
#include "CodeBlockParameter.h"
#include "CodeBlockVariableManager.h"

enum BlockSectionType
{
	BlockSectionStart,
	BlockSectionConditionalStart,
	BlockSectionBeginningStart,
	BlockSectionEndingStart,
	BlockSectionSpace,
	BlockSectionParameter,
	BlockSectionEnd
};

struct BlockSection
{
	BlockSectionType type;
	int size;
};

class CodeBlock : public Block
{
protected:
	GUIText* m_text;
	int m_parameters;
	bool m_condition = true;
	BLOCK_ID m_ID = BLOCK_ID_CUSTOM;

	std::vector<BlockSection> m_template;
	std::vector<SpriteSheetTile> m_tailTextureTiles;
	std::vector<SpriteSheetTile> m_tailEndTextureTiles;

	Hitbox2D* m_endHitbox = nullptr;
	

public:
	CodeBlock(SDL_Renderer* renderer, Transform transform, GameScene* gameScene, BLOCK_ID ID = BLOCK_ID_CUSTOM);
	~CodeBlock();

	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;
	void Resize() override;
	void Run() override;

	void CreateBlock() override;
	BLOCK_ID GetID();

	void CreateStartSegment(int* index);
	void CreateConditionalStartSegment(int* index);
	void CreateBeginningStartSegment(int* index);
	void CreateEndingStartSegment(int* index);

	void CreateSpaceSegment(int* index, int size);
	void CreateParameterSegment(int* index);
	void CreateEndSegment(int* index);

	void CreateTail();
	void CreateTailEnd();

	void Init(BLOCK_ID ID);
	void InitMountPoints();

	std::vector<MountPoint*>* GetParameterMountPoints();
	
};

