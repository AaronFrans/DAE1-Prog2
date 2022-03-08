#pragma once
#include "TextureManager.h"
#include "TearManager.h"
#include "Sprite.h"

class Isaac;

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
	TextureManager m_TextureManager;
	TearManager* m_pTearManager;

	Isaac* m_pPlayer;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;


	void InitPlayer();
	void DrawPlayer() const;
	void UpdatePlayer(float elapsedSec);
	void DeletePlayer();

	void InitTearManager();
	void DrawTearManager() const;
	void UpdateTearManager(float elapsedSec);
	void DeleteTearManager();
};