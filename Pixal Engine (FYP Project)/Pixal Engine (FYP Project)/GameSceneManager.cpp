#include "GameSceneManager.h"
GameSceneManager* GameSceneManager::m_instance = nullptr;

GameSceneManager::GameSceneManager(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
}

GameSceneManager::~GameSceneManager()
{
	m_renderer = nullptr;

	delete m_current_screen;
	m_current_screen = nullptr;
}

GameSceneManager* GameSceneManager::Instance(SDL_Renderer* renderer)
{
	if (!m_instance)
	{
		m_instance = new GameSceneManager(renderer);
	}
	return m_instance;
}

void GameSceneManager::Render()
{
	m_current_screen->Render();
}

void GameSceneManager::Update(float deltaTime, SDL_Event e)
{
	if (m_current_screen != nullptr) m_current_screen->Update(deltaTime, e);
}

//void GameSceneManager::ChangeScreen(SCREENS new_screen)
//{
//	// Deletes the old screen and creates a new one //
//	if (m_current_screen != nullptr)
//	{
//		switch (m_currentScreenType)
//		{
//		case SCREEN_LEVEL1:
//			delete (GameScreenLevel1*)m_current_screen;
//			break;
//		case SCREEN_MENU:
//			delete (GameScreenMainMenu*)m_current_screen;
//			break;
//		case SCREEN_INTRO:
//			delete (GameScreenIntro*)m_current_screen;
//			break;
//		case SCREEN_GAME_OVER:
//			delete (GameScreenGameOver*)m_current_screen;
//			break;
//		default:
//			delete m_current_screen;
//			break;
//		}
//	}
//	m_currentScreenType = new_screen;
//
//	GameScreenLevel1* tempScreen = nullptr;
//	GameScreenMainMenu* menuScreen = nullptr;
//	GameScreenIntro* introScreen = nullptr;
//	GameScreenGameOver* gameOverScreen = nullptr;
//
//
//	switch (new_screen)
//	{
//	case SCREEN_LEVEL1:
//		tempScreen = new GameScreenLevel1(m_renderer);
//		m_current_screen = (GameScreen*)tempScreen;
//		tempScreen = nullptr;
//		AudioManager::Instance()->SetAudioVolume(GAME_MUSIC, 32);
//		break;
//	case SCREEN_MENU:
//		menuScreen = new GameScreenMainMenu(m_renderer);
//		m_current_screen = (GameScreen*)menuScreen;
//		menuScreen = nullptr;
//		AudioManager::Instance()->SetAudioVolume(GAME_MUSIC, 64);
//		break;
//	case SCREEN_INTRO:
//		introScreen = new GameScreenIntro(m_renderer);
//		m_current_screen = (GameScreen*)introScreen;
//		introScreen = nullptr;
//		AudioManager::Instance()->SetAudioVolume(GAME_MUSIC, 64);
//		break;
//	case SCREEN_GAME_OVER:
//		gameOverScreen = new GameScreenGameOver(m_renderer);
//		m_current_screen = (GameScreen*)gameOverScreen;
//		gameOverScreen = nullptr;
//		AudioManager::Instance()->SetAudioVolume(GAME_MUSIC, 64);
//		break;
//	}
//}

bool GameSceneManager::GetQuit()
{
	return (GameScene*)m_current_screen->GetQuit();
}

