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
class StartScreen;

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
	static Window m_Window;

private:
	// DATA MEMBERS

	int m_Volume = 100;

	//Pointers
	World* m_pWorld;
	Player* m_pPlayer;
	Morphball* m_pMorphball;

	Point2f m_PlayerPosition{ 2000.f, 180.f };

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
	void DisplayInfo();
	void SaveGame(const std::string& name);
	void LoadGame(const std::string& name);

	//CREATE
	void CreateWorld();
	void CreateGameObjects();

	//DRAW
	void DrawGameObjects() const;
	void DrawHUD() const;

	//UPDATE
	void UpdateGameObjects(float elapsedSec);
};