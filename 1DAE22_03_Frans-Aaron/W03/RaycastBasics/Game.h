#pragma once
#include <vector>
#include "Vector2f.h"

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

	Point2f m_RayP1;
	Point2f m_RayP2;

	std::vector<Point2f> m_Surface;

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;

	void InitSurface();
	void DrawSurface() const;

	void DrawRaycast() const;

	void DrawVector(const Vector2f& v, const Point2f& p = Point2f{ 0, 0 }) const;
};