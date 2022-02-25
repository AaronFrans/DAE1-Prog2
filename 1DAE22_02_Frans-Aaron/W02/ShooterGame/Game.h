#pragma once
#include <vector>


class Enemy;
class Avatar;
class Game final
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update(float elapsedSec);
	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	// DATA MEMBERS
	const Window m_Window;

	static const int m_NrOfRows{ 4 };
	static const int m_NrOfColumns{ 10 };

	static const int m_MaxNrEnemies{ m_NrOfRows * m_NrOfColumns };

	static const int m_EnemySize{ 30 };
	static const int m_EnemyBorder{ 10 };
	static const int m_EnemyRectBorder{ 20 };


	Rectf m_PlayerBoundary{};
	Rectf m_EnemiesBoundary{};


	Enemy* m_pEnemies[m_MaxNrEnemies];

	Avatar* m_pPlayer;

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;

	void InitGameParams();

	void InitEnemies();
	void DeleteEnemies();
	void DrawEnemies() const;

	void InitPlayer();
	void DeletePlayer();
	void DrawPlayer() const;
	void UpdatePlayer(float elapsedSec);
};
