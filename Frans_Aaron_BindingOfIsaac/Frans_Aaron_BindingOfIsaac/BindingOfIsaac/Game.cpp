#include "pch.h"
#include "Game.h"
#include "Isaac.h"
#include "Poop.h"
#include "RoomManager.h"
#include "TearManager.h"
#include "IsaacHealthBar.h"
#include "UIManager.h"
#include "Room.h"
#include "Floor.h"

Game::Game(const Window& window)
	: m_Window{ window }
	, m_TextureManager{}
	, m_EnemyManager{ m_TextureManager }
	, m_Camera{ m_Window.width, m_Window.height }
	, m_CurrentRoom{ RoomManager::RoomLookup::startRoom }
{

	Initialize();

}
Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{


	IsaacHealthBar* isaacHealthBar = new IsaacHealthBar(m_TextureManager.GetTexture(TextureManager::TextureLookup::hearths),
		3, Point2f{ 0, m_Window.height - 20 });
	InitPlayer(isaacHealthBar);
	InitTearManager();
	InitUIManager(isaacHealthBar);
	isaacHealthBar = nullptr;
	m_pRoomManager = new RoomManager{ m_TextureManager, m_EnemyManager };

	InitFloor(m_pRoomManager);

	m_Camera.SetLevelBoundaries(m_pFloor->GetCurrentRoom()->GetBoundaries());
}

void Game::Cleanup()
{
	delete m_pRoomManager;
	DeleteTearManager();
	DeletePlayer();
	DeleteUIManager();
	DeleteFloor();
}

void Game::Update(float elapsedSec)
{
	time += elapsedSec;
	if (time > 5)
	{
		time -= 5;
		PrintFloor();
	}
	if (!m_pFloor->IsTransitioning())
	{
		UpdateTearManager(elapsedSec);
		UpdatePlayer(elapsedSec);
		m_pFloor->Update(elapsedSec, m_pPlayer);
	}
	else
	{
		m_Camera.SetLevelBoundaries(m_pFloor->GetCurrentRoom()->GetBoundaries());
		m_pFloor->DoneTransitioning();
	}

}

void Game::Draw() const
{

	ClearBackground();
	glPushMatrix();
	m_Camera.Transform(m_pPlayer->GetCenter());
	DrawFloor();
	m_pTearManager->DrawBackTears();
	DrawPlayer();
	m_pTearManager->DrawFrontTears();
	DrawUIManager();
	glPopMatrix();

}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.scancode)
	{
	case SDL_SCANCODE_KP_2:
		m_pPlayer->TakeDamage(0.5f);
		break;
	case SDL_SCANCODE_KP_3:
		m_pPlayer->TakeDamage(1.0f);
		break;
	}
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	m_pPlayer->ProcessKeyUpEvent(e);
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::InitPlayer(IsaacHealthBar* isaacHealthBar)
{
	m_pPlayer = new Isaac(m_TextureManager, isaacHealthBar, Point2f{ 100, 100 });
}

void Game::DrawPlayer() const
{
	m_pPlayer->Draw();
}

void Game::UpdatePlayer(float elapsedSec)
{
	m_pPlayer->Update(elapsedSec, m_pTearManager, m_TextureManager, m_pFloor->GetCurrentRoom());
}

void Game::DeletePlayer()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void Game::InitTearManager()
{
	m_pTearManager = new TearManager{};
}

void Game::UpdateTearManager(float elapsedSec)
{
	m_pTearManager->UpdateTears(elapsedSec, m_pFloor->GetCurrentRoom()->GetGameObjects(), m_pFloor->GetCurrentRoom()->GetEnemies());
}

void Game::DeleteTearManager()
{
	delete m_pTearManager;
	m_pTearManager = nullptr;
}

void Game::InitUIManager(IsaacHealthBar* isaacHealthBar)
{
	m_pUIManager = new UIManager(isaacHealthBar);
}

void Game::DrawUIManager() const
{
	m_pUIManager->Draw(m_Camera.GetCameraView(m_pPlayer->GetCenter()));
}

void Game::DeleteUIManager()
{
	delete m_pUIManager;
}

void Game::InitFloor(RoomManager* roomManager)
{
	m_pFloor = new Floor{};
	m_pFloor->GenerateFloor(roomManager);
	m_pFloor->ActivateDoors();
	m_pFloor->InitEnemies(m_EnemyManager);
}

void Game::DrawFloor() const
{
	m_pFloor->Draw();
}

void Game::DeleteFloor()
{
	delete m_pFloor;
}

void Game::PrintFloor()
{
	testAlgo = m_pFloor->GetLayout();
	std::cout << '\n';
	std::cout << '\n';
	for (int i = 8; i >= 0; i--)
	{

		for (int j = 0; j < 9; j++)
		{
			std::cout << testAlgo[i * 9 + j];
		}
		std::cout << '\n';
	}
	std::cout << '\n';
	std::cout << '\n';
}
