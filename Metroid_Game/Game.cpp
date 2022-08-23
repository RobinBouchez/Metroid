#include "pch.h"
#include "Game.h"

#include "World.h"
#include "Player.h"
#include "Camera.h"
#include "Morphball.h"
#include "Vitals.h"
#include "HUD.h"
#include "Level.h"

//Scenes
#include "StartScreen.h"
#include "GameOverScreen.h"
#include "MenuScreen.h"
#include "Screen.h"

//Inlcude Managers
#include "SoundManager.h"
#include "CrawlerEnemy.h"
#include "SkrullEnemy.h"
#include "TextureManager.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "ScreenManager.h"
#include "PickUpManager.h"
#include "LevelManager.h"

//Extrernal includes
#include <iostream>
#include <fstream>

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

Window Game::m_Window{};

Game::Game( const Window& window ) 
{
	m_Window = window;
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	std::cout << "Press the 'i' key to display the game's info." << std::endl;
	
	ScreenManager::GetInstance().Add(new StartScreen(Point2f{ m_Window.width / 2 - 570, 0 }, m_Window));

	SoundManager::GetInstance().CreateSound("Music", ".mp3");
	SoundManager::GetInstance().PlayLoop("Music");

	CreateWorld();
	CreateGameObjects();

}

void Game::Cleanup( )
{
	SaveGame("GameData");
	m_pWorld->CleanUp();

	delete m_pWorld;
	m_pWorld = nullptr;

	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pMorphball;
	m_pMorphball = nullptr;

	SoundManager::GetInstance().Cleanup();
	EnemyManager::GetInstance().Cleanup(); 
	BulletManager::GetInstance().Cleanup();
	ScreenManager::GetInstance().Cleanup();
	PickUpManager::GetInstance().Cleanup();
	TextureManager::GetInstance().Cleanup();

}

void Game::Update( float elapsedSec )
{
	if (ScreenManager::GetInstance().GetCurrent()->IsActive())
	{
		ScreenManager::GetInstance().GetCurrent()->Update(elapsedSec);
		return;
	}
	UpdateGameObjects(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );

	if (ScreenManager::GetInstance().GetCurrent()->IsActive())
	{
		ScreenManager::GetInstance().GetCurrent()->Draw();
		return;
	}
	glPushMatrix();
	m_pWorld->GetLevel()->m_pCamera->Transform(m_pPlayer->m_Shape);
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
	case SDLK_SPACE:
		if (ScreenManager::GetInstance().GetCurrent()->IsActive())
		{
			ScreenManager::GetInstance().Replace(new MenuScreen(Point2f{ m_Window.width / 2 - 570, 0 }, m_Window));
		}
		break;
	case SDLK_m:
		SoundManager::GetInstance().SetVolume(m_Volume - m_Volume);
		break;
	case SDLK_COMMA:
		SoundManager::GetInstance().SetVolume(m_Volume -= 10);
		break;
	case SDLK_PERIOD:
		SoundManager::GetInstance().SetVolume(m_Volume += 10);
		break;
	case SDLK_RETURN:
		if (MenuScreen::m_SaveGame)
		{
			LoadGame("GameData");
		}
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
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
	std::cout << "Press the space bar to start the game" << std::endl;
	std::cout << "Use the arrow keys to select an option in the menu" << std::endl;
	std::cout << "Press Enter/Return to confirm" << std::endl;
	std::cout << "Use the 'w' 'a' 's' 'd' keys to move the player " << std::endl;
	std::cout << "Or use the arrow keys to also  move the player " << std::endl;
	std::cout << "Use the space bar to jump" << std::endl;
	std::cout << "Use the 'f' key to fire" << std::endl;
}

void Game::CreateWorld()
{
	m_pWorld = new World();
}

void Game::CreateGameObjects()
{
	m_pPlayer = new Player( m_PlayerPosition );

	m_pMorphball = new Morphball();

	m_pWorld->LoadEnemies();
}

void Game::DrawGameObjects() const
{
	m_pWorld->Draw();
	m_pPlayer->Draw();
	m_pMorphball->Draw();

	BulletManager::GetInstance().Draw();
	EnemyManager::GetInstance().Draw();
	PickUpManager::GetInstance().Draw();
}

void Game::DrawHUD() const
{
	const float border = 200.f;
	const float x = m_pWorld->GetLevel()->m_pCamera->GetPosition().x + border;
	const float y = m_Window.height - border;

	HUD::GetInstance().Draw(x, y);
}

void Game::UpdateGameObjects(float elapsedSec)
{
	if (m_pPlayer->GetVitals()->GetHealth() == 0)
	{
		ScreenManager::GetInstance().Add(new GameOverScreen(Point2f{ m_Window.width / 2 - 570, 0 }, m_Window));
	}

	m_pPlayer->Update(elapsedSec, m_pWorld);

	m_pMorphball->CheckIfhit(m_pPlayer);
	m_pMorphball->Update(elapsedSec);

	EnemyManager::GetInstance().Update(elapsedSec, m_pWorld, m_pPlayer);
	BulletManager::GetInstance().Update(elapsedSec);
	PickUpManager::GetInstance().Update(elapsedSec);

	m_pWorld->Update(elapsedSec);
}

void Game::SaveGame(const std::string& name)
{
	std::ofstream file(name + ".txt"); //Create file

	//write data to file
	file << m_pWorld->m_LevelIndex << '\n';
	file << m_pPlayer->m_Shape.left << '\n';
	file << m_pPlayer->m_Shape.bottom << '\n';
	file << m_pPlayer->GetVitals()->GetHealth() << '\n';
	file << m_pPlayer->GetScore();
	file << EnemyManager::GetInstance();
	file.close();
}

void Game::LoadGame(const std::string& name)
{
	std::ifstream file{ name + ".txt" };
	
	std::string index{};
	std::getline(file, index);
	m_pWorld->m_LevelIndex = std::stoi(index);

	std::string x{};
	std::getline(file, x);
	std::string y{};
	std::getline(file, y);

	m_pPlayer->SetPosition(Point2f{ std::stof(x), std::stof(y) });

	std::string health{};
	std::getline(file, health);
	m_pPlayer->GetVitals()->SetHealth(std::stof(health));

	std::string Score{};
	std::getline(file, Score);
	m_pPlayer->m_Score = std::stoi(Score);

	file >> EnemyManager::GetInstance();

	file.close();
}
