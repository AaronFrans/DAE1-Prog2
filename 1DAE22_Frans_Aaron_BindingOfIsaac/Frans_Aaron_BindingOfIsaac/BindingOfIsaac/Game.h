#pragma once
#include "TextureManager.h"
#include "Sprite.h"
#include "Camera.h"



//TODO: 7. make Room class
//TODO: 8. make enemy class, base = GameObject
//TODO: 10. make GameObjectManager class
//TODO: 11. make Healthbar class
//TODO: 12. make Minimap class
//TODO: 13. UI Class, has Healthbar, Minimap ...
//TODO: 14. Rooms via array -> random index... boss and start room seperate
//TODO: 15. Think about transition between floors
//TODO: 16. Rock class
//TODO: 17. Make SpriteManager to determine Draw Order

class Isaac;
class RoomManager;
class TearManager;
class IsaacHealthBar;
class SmallSpider;

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
	Camera m_Camera;
	TextureManager m_TextureManager;
	RoomManager* m_pRoomManager;
	TearManager* m_pTearManager;

	SmallSpider* testSpider;

	Isaac* m_pPlayer;

	IsaacHealthBar* healthTest;


	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;


	void InitPlayer();
	void DrawPlayer() const;
	void UpdatePlayer(float elapsedSec);
	void DeletePlayer();

	void InitTearManager();
	void UpdateTearManager(float elapsedSec);
	void DeleteTearManager();
};