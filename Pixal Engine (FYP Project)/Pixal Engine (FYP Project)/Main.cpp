#include "Commons.h"
#include "GameObject.h"
#include "TextureLoader.h"
#include "AudioManager.h"
#include "GameSceneManager.h"
#include "CodeBlockScript.h"
#include "GUICanvas.h"

#include "SDL.h"
#include "SDL_image.h"
#include <SDL_mixer.h>
#include <iostream>
#include <math.h>
#include <SDL_ttf.h>

// Globals //
SDL_Window* engine_window = nullptr;
SDL_Renderer* engine_renderer = nullptr;

SDL_Window* game_window = nullptr;
SDL_Renderer* game_renderer = nullptr;

TextureLoader* textureLoader = nullptr;
AudioManager* audioManager = nullptr;
GameSceneManager* sceneManager = nullptr;

CodeBlockScript* mainScript = nullptr;
CodeBlockScript* emptyScript = nullptr;
std::vector<CodeBlockScript*> scripts;
int selectedScript = 0;
GUIText* scriptText = nullptr;
GUICanvas* EngineGUI = nullptr;
GUICanvas* BlockSelectGUI = nullptr;

std::vector<CodeBlock*> BlockDrawer;

Uint32 g_old_time;
float deltaTime;

void InitGUI() 
{
	// Create GUI at top of screen //
	EngineGUI = new GUICanvas(engine_renderer, Vector2D(ENGINE_SCREEN_WIDTH, ENGINE_SCREEN_HEIGHT / 8), ENGINE_BACKGROUND_COLOUR, { {Vector2D(0,0),Vector2D(1,1),0},COLLISION_NONE });
	
	GUIText* text = new GUIText(engine_renderer, { {Vector2D(0,0),Vector2D(1,1),0},COLLISION_NONE }, { "Pixal Engine",ENGINE_FONT_PATH,15,ENGINE_TEXT_COLOUR });
	EngineGUI->AddText((GameObject*)text);

	scriptText = new GUIText(engine_renderer, { {Vector2D(0,10),Vector2D(1,1),0},COLLISION_NONE }, { scripts[selectedScript]->GetName(),ENGINE_FONT_PATH,40,ENGINE_TEXT_COLOUR });
	EngineGUI->AddText((GameObject*)scriptText);

	// Create tabs for all available scripts //
	int i = 0;
	Vector2D ButtonSize = { 100,30 };
	for (CodeBlockScript* script : scripts) 
	{
		Vector2D ButtonPos = Vector2D(i * ButtonSize.x, ENGINE_SCREEN_HEIGHT / 8 - ButtonSize.y);

		GUIText* tabText = new GUIText(engine_renderer, { {Vector2D(0,35),Vector2D(1,1),0},COLLISION_NONE }, { script->GetName(),ENGINE_FONT_PATH,20,ENGINE_TEXT_COLOUR });
		GUIButton* scriptButton = new GUIButton(engine_renderer, ButtonSize, ENGINE_BUTTON_COLOURS, { {ButtonPos,ButtonSize,0},COLLISION_NONE });
		
		scriptButton->SetText(tabText);

		EngineGUI->AddButton(scriptButton);
		i++;
	}
	
	// Create Block Drawer GUI //
	BlockSelectGUI = new GUICanvas(engine_renderer, Vector2D(ENGINE_SCREEN_WIDTH, ENGINE_SCREEN_HEIGHT / 8.f), ENGINE_BUTTON_COLOURS.defaultColour, { {Vector2D(0,ENGINE_SCREEN_HEIGHT - (ENGINE_SCREEN_HEIGHT / 8)),Vector2D(1,1),0},COLLISION_NONE });
	int blockButtonWidth = 30;

	GUIText* left = new GUIText(engine_renderer, { {Vector2D(0,10),Vector2D(1,1),0},COLLISION_NONE }, { "<",ENGINE_FONT_PATH,40,ENGINE_TEXT_COLOUR });
	GUIButton* blockLeft = new GUIButton(engine_renderer, Vector2D(blockButtonWidth, ENGINE_SCREEN_HEIGHT / 8.f), ENGINE_BUTTON_COLOURS, { {Vector2D(0,ENGINE_SCREEN_HEIGHT - (ENGINE_SCREEN_HEIGHT / 8)),Vector2D(1,1),0},COLLISION_NONE });
	blockLeft->SetText(left);
	BlockSelectGUI->AddButton(blockLeft);

	GUIText* right = new GUIText(engine_renderer, { {Vector2D(0,10),Vector2D(1,1),0},COLLISION_NONE }, { ">",ENGINE_FONT_PATH,40,ENGINE_TEXT_COLOUR });
	GUIButton* blockRight = new GUIButton(engine_renderer, Vector2D(blockButtonWidth, ENGINE_SCREEN_HEIGHT / 8.f), ENGINE_BUTTON_COLOURS, { {Vector2D(ENGINE_SCREEN_WIDTH - blockButtonWidth,ENGINE_SCREEN_HEIGHT - (ENGINE_SCREEN_HEIGHT / 8)),Vector2D(1,1),0},COLLISION_NONE });
	blockRight->SetText(right);
	BlockSelectGUI->AddButton(blockRight);

	// Populate Block Drawer with Codeblocks //
	float shrinkFactor = 2;
	float x = blockButtonWidth;
	int blockDrawerSpacing = 128;

	for (int ID = 0; ID < BLOCK_ID_END_ID; ID++) 
	{
		CodeBlock* block = new CodeBlock(engine_renderer, { Vector2D(0, 0) ,Vector2D(1,1),0 }, (BLOCK_ID)ID);
		block->SetPosition(Vector2D(x, ENGINE_SCREEN_HEIGHT - ((ENGINE_SCREEN_HEIGHT / 8.f) - 20)) * shrinkFactor);
		x += (block->GetHitboxes()[0]->size.x) / shrinkFactor;

		block->SetScale(Vector2D(1 / shrinkFactor, 1 / shrinkFactor));
		BlockDrawer.push_back(block);
	}
}

bool InitEditorWindow()
{
	//////////////// Create Engine Window ////////////////////

	// Setup passed so create window //
	engine_window = SDL_CreateWindow
	(
		"Pixal Engine",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		ENGINE_SCREEN_WIDTH,
		ENGINE_SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	// Did window get created? //
	if (engine_window == nullptr)
	{
		// Window failed //
		std::cout << "!! Engine window was not created. Error: " << SDL_GetError() << "!!\n";
		return false;
	}

	engine_renderer = SDL_CreateRenderer(engine_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(engine_renderer, SDL_BLENDMODE_BLEND);

}

bool InitGameWindow() 
{
	////////// Create Game Window ////////////////

		// Setup passed so create window //
	game_window = SDL_CreateWindow
	(
		"Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		GAME_SCREEN_WIDTH,
		GAME_SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	// Did window get created? //
	if (game_window == nullptr)
	{
		// Window failed //
		std::cout << "!! Game window was not created. Error: " << SDL_GetError() << "!!\n";
		return false;
	}

	game_renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(game_renderer, SDL_BLENDMODE_BLEND);

}

bool InitSDL()
{
	// Setup SDL //
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "!! SDL did not initialise. Error: " << SDL_GetError() << "!!\n";
		return false;
	}

	InitGameWindow();
	InitEditorWindow();

	// Set Icon //
	SDL_Surface* icon = IMG_Load(GAME_ICON_PATH);

	if (icon != NULL)
	{
		SDL_SetWindowIcon(engine_window, icon);
		SDL_SetWindowIcon(game_window, icon);
	}
	else std::cout << "!! " << SDL_GetError() << " !!\n";

	if (engine_renderer != nullptr && game_renderer != nullptr)
	{
		// Init PNG loading //
		int imageFlags = IMG_INIT_PNG;

		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			std::cout << "!! SDL_Image could not initialise. Error: " << IMG_GetError() << "!!\n";
		}
	}
	else
	{
		std::cout << "!! Renderer could not initialise. Error: " << SDL_GetError() << "!!\n";
	}

	if (TTF_Init())
	{
		std::cout << "!! TTF could not initialise. Error: " << TTF_GetError() << " !!\n";
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "!! Mixer could not initialise. Error: " << Mix_GetError() << "!!\n";
	}

	return true;

}

bool InitAll()
{
	bool success = false;

	success = InitSDL();

	audioManager = AudioManager::Instance();
	textureLoader = TextureLoader::Instance(engine_renderer);
	sceneManager = GameSceneManager::Instance(engine_renderer);
	mainScript = new CodeBlockScript(engine_renderer);
	mainScript->SetName("Main");


	CodeBlock* codeBlock = new CodeBlock(engine_renderer, Transform{ {100,100},{1,1},0 },BLOCK_ID_SET_POSITION);
	CodeBlock* codeBlock1 = new CodeBlock(engine_renderer, Transform{ {400,400},{1,1},0 }, BLOCK_ID_STOP);
	CodeBlock* codeBlock3 = new CodeBlock(engine_renderer, Transform{ {300,-100},{1,1},0 }, BLOCK_ID_IF);
	CodeBlock* codeBlock4 = new CodeBlock(engine_renderer, Transform{ {30,-50},{1,1},0 }, BLOCK_ID_CUSTOM);
	CodeBlock* codeBlock5 = new CodeBlock(engine_renderer, Transform{ {30,-60},{1,1},0 }, BLOCK_ID_CUSTOM);
	CodeBlock* codeBlock6 = new CodeBlock(engine_renderer, Transform{ {30,-70},{1,1},0 }, BLOCK_ID_CUSTOM);
	CodeBlock* codeBlock7 = new CodeBlock(engine_renderer, Transform{ {30,-80},{1,1},0 }, BLOCK_ID_CUSTOM);
	CodeBlockParameter* param = new CodeBlockParameter(engine_renderer, Transform{ {100,400},{1,1},0 });
	CodeBlockParameter* param1 = new CodeBlockParameter(engine_renderer, Transform{ {100,600},{1,1},0 });

	mainScript->Add(codeBlock);
	mainScript->Add(codeBlock1);
	mainScript->Add(codeBlock3);
	mainScript->Add(codeBlock4);
	mainScript->Add(codeBlock5);
	mainScript->Add(codeBlock6);
	mainScript->Add(codeBlock7);
	mainScript->Add(param);
	mainScript->Add(param1);

	scripts.push_back(mainScript);

	emptyScript = new CodeBlockScript(engine_renderer);
	emptyScript->SetName("Other Script");

	CodeBlock* codeBlockE = new CodeBlock(engine_renderer, Transform{ {30,80},{1,1},0 }, BLOCK_ID_CUSTOM);
	emptyScript->Add(codeBlockE);

	scripts.push_back(emptyScript);

	InitGUI();

	return success;
}

void CloseSDL()
{

	SDL_DestroyRenderer(engine_renderer);
	engine_renderer = nullptr;
	SDL_DestroyRenderer(game_renderer);
	game_renderer = nullptr;

	// Release the window //
	SDL_DestroyWindow(engine_window);
	engine_window = nullptr;

	SDL_DestroyWindow(game_window);
	game_window = nullptr;

	// quit SDL subsystems //
	SDL_Quit();
}

void Render()
{
	SDL_SetRenderDrawColor(engine_renderer, 0, 0, 0, 255);
	SDL_RenderClear(engine_renderer);

	SDL_SetRenderDrawColor(game_renderer, 0, 0, 100, 255);
	SDL_RenderClear(game_renderer);

	SDL_SetRenderDrawColor(engine_renderer, 0, 100, 0, 255);

	scripts[selectedScript]->Render();
	EngineGUI->Render();

	BlockSelectGUI->Render();
	for (Block* block : BlockDrawer) 
	{
		block->Render();
	}

	SDL_RenderPresent(engine_renderer);
	SDL_RenderPresent(game_renderer);
}


bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	

	// Event handler //
	SDL_Event e;

	// Get events //
	SDL_PollEvent(&e);

	switch (e.type)
	{
		
	case SDL_WINDOWEVENT:
		switch (e.window.event)
		{
			// Click X to quit //
		case SDL_WINDOWEVENT_CLOSE:
			return true;
			break;
		}
		break;
	}

	deltaTime = new_time - g_old_time;

	scripts[selectedScript]->Update(deltaTime, e);

	InputManager::Instance()->Update(deltaTime, e);
	
	EngineGUI->Update(deltaTime, e);

	BlockSelectGUI->Update(deltaTime, e);

	Vector2D mousePos = InputManager::Instance()->GetMousePos();

	for (CodeBlock* block : BlockDrawer) 
	{
		block->Update(deltaTime, e);
		if (block->GetHitboxes()[0]->ContainsPoint(mousePos * 2)) 
		{
			if (InputManager::Instance()->GetMouseLeftClicked() && !scripts[selectedScript]->IsBlockSelected())
			{
				CodeBlock* newBlock = new CodeBlock(engine_renderer, { mousePos / scripts[selectedScript]->GetZoomValue(),{1,1},0}, block->GetID());

				scripts[selectedScript]->Add(newBlock);
				scripts[selectedScript]->SelectBlock((Block*)newBlock);
			}
		}
	}

	g_old_time = new_time;

	// Handle GUI Inputs //
	int index = 0;
	for (GUIButton* button : EngineGUI->GetAttachedButtons()) 
	{
		if (button->GetClicked() && !InputManager::Instance()->GetMouseLeftClicked()) 
		{
			// Switch Scripts //
			
			selectedScript = index;
			scriptText->SetText(scripts[selectedScript]->GetName());
			scriptText->ReformatText();
				
			button->ResetClicked();
		}
		index++;
	}

	return false;
}

int main(int argc, char* argv[])
{
	if (InitAll())
	{
		g_old_time = SDL_GetTicks();

		bool quit = false;

		// Game loop //
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	CloseSDL();

	return 0;
}