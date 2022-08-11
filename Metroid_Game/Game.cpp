#include "pch.h"
#include "Game.h"
#include "World.h"
#include "Player.h"
#include "Camera.h"
#include "Morphball.h"
#include "SoundManager.h"
#include "CrawlerEnemy.h"
#include "SkrullEnemy.h"
#include "TextureManager.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "HUD.h"
#include <iostream>

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	std::cout << "Press the 'i' key to display the game's info." << std::endl;
	
	CreateWorld();
	CreateGameObjects();
	CreateCamera();
	CreateSoundManager();
	CreateHUD();
}

void Game::Cleanup( )
{

	delete m_pWorld;
	m_pWorld = nullptr;

	delete m_pHUD;
	m_pHUD = nullptr;

	delete m_pCamera;
	m_pCamera = nullptr;

	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pMorphball;
	m_pMorphball = nullptr;

	SoundManager::GetInstance().Cleanup();
	TextureManager::GetInstance().Cleanup();
	EnemyManager::GetInstance().Cleanup(); 
	BulletManager::GetInstance().Cleanup();
}

void Game::Update( float elapsedSec )
{
	UpdateGameObjects(elapsedSec);
	UpdateHUD(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );

	glPushMatrix();
		m_pCamera->Transform(m_pPlayer->GetShape());
		DrawWorld();
		DrawGameObjects();
		DrawHUD();
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_i:
		DisplayInfo();
		break;
	case SDLK_m:
		m_pSoundManager->SetVolume(m_Volume -= m_Volume);
		break;
	case SDLK_COMMA:
		m_Volume -= 10;
		m_pSoundManager->SetVolume(m_Volume);
		break;
	case SDLK_PERIOD:
		m_Volume += 10;
		m_pSoundManager->SetVolume(m_Volume);
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DisplayInfo()
{
	std::cout << "----- GAME INFO -----" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Game: Original Metroid SNES" << std::endl;
	std::cout << "Made by: Robin Bouchez" << std::endl;
	
	std::cout << "----- GAME CONTROLS -----" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Use the 'w' 'a' 's' 'd' keys to move the player " << std::endl;
	std::cout << "Or use the arrow keys to also  move the player " << std::endl;
	std::cout << "Use the space bar to jump" << std::endl;
	std::cout << "Use the 'f' key to fire" << std::endl;
}

void Game::CreateWorld()
{
	m_pWorld = new World(m_Window.height, m_Window.width);
}

void Game::CreateGameObjects()
{
	m_pPlayer = new Player(m_PlayerPosition);

	m_pMorphball = new Morphball();

	EnemyManager::GetInstance().Add(new CrawlerEnemy{ Point2f{1900.f, 612.f} });
	EnemyManager::GetInstance().Add(new CrawlerEnemy{ Point2f{2250.f, 500.f } });

	EnemyManager::GetInstance().Add(new SkrullEnemy{ Point2f{2250.f, 500.f } });
	EnemyManager::GetInstance().Add(new SkrullEnemy{ Point2f{2250.f, 500.f } });

}

void Game::CreateCamera()
{
	m_pCamera = new Camera(m_Window.width, m_Window.height);
	
	m_pCamera->SetLevelBoundaries(m_pWorld->GetX(), m_pWorld->GetY(), m_pWorld->GetWidth(), m_pWorld->GetHeight());
}

void Game::CreateSoundManager()
{
	
	//m_pSoundManager->PlayLoop("Music");
}

void Game::CreateHUD()
{
	m_pHUD = new HUD();
}

void Game::DrawWorld() const
{
	m_pWorld->Draw();
}

void Game::DrawGameObjects() const
{
	m_pPlayer->Draw();
	EnemyManager::GetInstance().Draw();
	m_pMorphball->Draw();
	BulletManager::GetInstance().Draw();
}

void Game::DrawHUD() const
{
	float border = 150.f;
	float x = m_pPlayer->GetShape().left - m_Window.width / 2 + border / 2;
	float y = m_Window.height - border;
	m_pHUD->Draw(x, y);
}

void Game::UpdateGameObjects(float elapsedSec)
{
	m_pPlayer->Update(elapsedSec, m_pWorld);
	EnemyManager::GetInstance().Update(elapsedSec);
	m_pMorphball->CheckIfhit(m_pPlayer);
	m_pMorphball->Update(elapsedSec);
	BulletManager::GetInstance().Update(elapsedSec);
}

void Game::UpdateHUD(float elapsedSec)
{
	m_pHUD->Update(elapsedSec);
}

void Game::DeleteGameObjects()
{

}
