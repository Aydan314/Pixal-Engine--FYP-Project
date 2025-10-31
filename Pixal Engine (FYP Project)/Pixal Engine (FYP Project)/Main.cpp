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
CodeBlockScript* currentScript = nullptr;
GUICanvas* EngineGUI = nullptr;

Uint32 g_old_time;
float deltaTime;

void Render()
{
	SDL_SetRenderDrawColor(engine_renderer, 0, 0, 0, 255);
	SDL_RenderClear(engine_renderer);

	SDL_SetRenderDrawColor(game_renderer, 0, 0, 100, 255);
	SDL_RenderClear(game_renderer);

	SDL_SetRenderDrawColor(engine_renderer, 0, 100, 0, 255);

	currentScript->Render();
	EngineGUI->Render();

	SDL_RenderPresent(engine_renderer);
	SDL_RenderPresent(game_renderer);
}

void InitGUI() 
{
	EngineGUI = new GUICanvas(engine_renderer, Vector2D(ENGINE_SCREEN_WIDTH, ENGINE_SCREEN_HEIGHT / 8), { 50,50,50,255 }, { {Vector2D(0,0),Vector2D(1,1),0},COLLISION_NONE });
	
	GUIText* text = new GUIText(engine_renderer, { {Vector2D(0,0),Vector2D(1,1),0},COLLISION_NONE }, { "Pixal Engine",ENGINE_FONT_PATH,15,{255,255,255,255} });
	EngineGUI->AddText((GameObject*)text);

	GUIText* scriptText = new GUIText(engine_renderer, { {Vector2D(0,35),Vector2D(1,1),0},COLLISION_NONE }, { currentScript->GetName(),ENGINE_FONT_PATH,30,{255,255,255,255}});
	EngineGUI->AddText((GameObject*)scriptText);
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


	CodeBlock* codeBlock = new CodeBlock(engine_renderer, Transform{ {100,100},{1,1},0 }, SpriteSheetTexture{ "Engine Images/CodeBlockSheet.png",{8,8},{0,0} });
	CodeBlock* codeBlock1 = new CodeBlock(engine_renderer, Transform{ {400,400},{1,1},0 }, SpriteSheetTexture{ "Engine Images/CodeBlockSheet.png",{8,8},{0,0} });
	CodeBlockParameter* param = new CodeBlockParameter(engine_renderer, Transform{ {100,400},{1,1},0 }, SpriteSheetTexture{ "Engine Images/CodeBlockSheet.png",{8,8},{0,0} });

	mainScript->Add(codeBlock);
	mainScript->Add(codeBlock1);
	//mainScript->Add(param);

	currentScript = mainScript;

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

	currentScript->Update(deltaTime, e);

	InputManager::Instance()->Update(deltaTime, e);

	EngineGUI->Update(deltaTime, e);

	g_old_time = new_time;

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