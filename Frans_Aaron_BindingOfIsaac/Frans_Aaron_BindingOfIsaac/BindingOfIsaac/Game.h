#pragma once
#pragma once
#include "TextureManager.h"
#include "Sprite.h"
#include "Camera.h"
#include "RoomManager.h"

class Isaac;
class TearManager;
class UIManager;
class IsaacHealthBar;
class Floor;
class ItemManager;
class Monstro;
class SoundEffectManager;
class EnemyManager;
class MenuScreen;
class PickUpManager;
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

	enum class GameState
	{
		startMenu,
		playing,
		death,
		victory
	};

	// DATA MEMBERS
	const Window m_Window;
	Camera m_Camera;
	TextureManager m_TextureManager;
	EnemyManager* m_pEnemyManager;
	RoomManager* m_pRoomManager;
	TearManager* m_pTearManager;
	UIManager* m_pUIManager;
	ItemManager* m_pItemManager;
	SoundEffectManager* m_pSoundEffectManager;
	PickUpManager* m_pPickUpManager;

	MenuScreen* m_pStartScreen;
	MenuScreen* m_pDeathScreen;
	MenuScreen* m_pVictoryScreen;
	Floor* m_pFloor;
	Isaac* m_pPlayer;




	bool m_IsDeathScreenSfxPlaying;
	float m_DeathScreenSfxAccuTime;
	float m_DeathScreenSfxMaxTime;


	GameState m_State;


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

	void InitFloor(RoomManager* roomManager);
	void DrawFloor() const;
	void DeleteFloor();

	void PrintInfo();


};