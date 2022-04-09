#pragma once
#include <vector>

#include "Matrix2x3.h"

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

	std::vector<Point2f> m_Vertices;
	std::vector<Point2f> m_TransformedVertices;

	float m_ScaleFactor;
	float m_Angle;
	Vector2f m_Translate;

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
};