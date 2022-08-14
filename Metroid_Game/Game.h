#pragma once
#include <vector>

class World;
class Player;
class Camera;
class Morphball;
class SoundManager;
class vector;
class HUD;
class Enemy;

class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;

	int m_Volume = 100;

	World* m_pWorld;
	Player* m_pPlayer;
	Camera* m_pCamera;
	Morphball* m_pMorphball;
	SoundManager* m_pSoundManager;
	
	Point2f m_PlayerPosition{ 2000.f, 200.f };

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
	void DisplayInfo();

	//CREATE
	void CreateWorld();
	void CreateGameObjects();
	void CreateCamera();
	void CreateSoundManager();

	//DRAW
	void DrawWorld() const;
	void DrawGameObjects() const;
	void DrawHUD() const;

	//UPDATE
	void UpdateGameObjects(float elapsedSec);
};