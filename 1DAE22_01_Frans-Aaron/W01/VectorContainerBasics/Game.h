#pragma once
#include <vector>


class Card;

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


	std::vector<int> m_Numbers1{  };
	std::vector<int> m_Numbers2{ 10, 6, 5, 7 };

	std::vector<Card*> m_Cards{};


	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void AddIntToVector(std::vector<int>& v);
	void RemoveLastFromVector(std::vector<int>& v);

	void IncrementVectorMembers(std::vector<int>& v);
	void DecrementVectorMembers(std::vector<int>& v);

	void PrintVector(std::vector<int>& v);

	void InitCards();
	void DrawCards() const;
	void DeleteCard();

	void ShuffleCards();
};