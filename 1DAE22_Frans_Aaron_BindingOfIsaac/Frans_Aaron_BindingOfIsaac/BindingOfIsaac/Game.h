#pragma once
#include "TextureManager.h"
#include "Sprite.h"
#include "Camera.h"
#include "RoomManager.h"
#include "EnemyManager.h"
//TODO: 14. Room Templates via array -> recursive to make floor ... boss and start room seperate
//TODO: 15. Think about transition between floors
//TODO: 16. Make SpriteManager to determine Draw Order

class Isaac;
class TearManager;
class UIManager;
class IsaacHealthBar;
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
	EnemyManager m_EnemyManager;
	RoomManager* m_pRoomManager;
	TearManager* m_pTearManager;
	UIManager* m_pUIManager;

	Isaac* m_pPlayer;
	RoomManager::RoomLookup m_CurrentRoom;

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;


	void InitPlayer(IsaacHealthBar* isaacHealthBar);
	void DrawPlayer() const;
	void UpdatePlayer(float elapsedSec);
	void DeletePlayer();

	void InitTearManager();
	void UpdateTearManager(float elapsedSec);
	void DeleteTearManager();

	void InitUIManager(IsaacHealthBar* isaacHealthBar);
	void DrawUIManager() const;
	void DeleteUIManager();
};