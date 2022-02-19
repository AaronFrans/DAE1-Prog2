#pragma once
#include "PowerUp.h"
class Game final
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
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

	Point2f m_MousePos;
	static const int m_NrPowerUps{ 10 };
	PowerUp* m_pPowerUps[m_NrPowerUps];
	Point2f m_PowerUpsCenters[m_NrPowerUps];
	PowerUp::Type m_PowerUpTypes[m_NrPowerUps];
	bool m_PowerUpsDestroyed[m_NrPowerUps];
	float m_PowerUpRadius;
	int m_ActNrPowerUps;
	Rectf m_Destroyer;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void ShowTestMessage( ) const;
	void ShowNrPowerUps( ) const;
	void CreatePowerUps( );
	void UpdatePowerUps( float elapsedSec );
	void DrawPowerUps( ) const;
	void DeletePowerUps( );

	void MoveDestroyer( const Point2f& newCenter );
	void DrawDestroyer( ) const;
	void VerifyOverlapping( );
};


