#include "pch.h"
#include "Game.h"
#include "Isaac.h"
#include "Poop.h"
#include "Room.h"
#include "RoomManager.h"
#include "TearManager.h"
#include "IsaacHealthBar.h"
#include "UIManager.h"
#include "SmallSpider.h"

Game::Game(const Window& window)
	: m_Window{ window }
	, m_TextureManager{}
	, m_Camera{ m_Window.width, m_Window.height }
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
	m_pRoomManager = new RoomManager{ m_TextureManager };
	m_Camera.SetLevelBoundaries(m_pRoomManager->GetRoom(RoomManager::RoomLookup::bigRoom2)->GetBoundaries());
	testSpider = new SmallSpider{
		m_TextureManager.GetTexture(TextureManager::TextureLookup::smallSpiderMovement),
		m_TextureManager.GetTexture(TextureManager::TextureLookup::smallSpiderDeath),
		 m_pPlayer->GetCenter(), 0.5f,150 };

}

void Game::Cleanup()
{
	delete m_pRoomManager;
	delete testSpider;
	DeleteTearManager();
	DeletePlayer();
	DeleteUIManager();
}

void Game::Update(float elapsedSec)
{
	UpdateTearManager(elapsedSec);
	UpdatePlayer(elapsedSec);
	testSpider->Update(elapsedSec, m_pRoomManager->GetRoom(RoomManager::RoomLookup::bigRoom2), m_pPlayer);
}

void Game::Draw() const
{

	ClearBackground();
	glPushMatrix();
	m_Camera.Transform(m_pPlayer->GetCenter());
	m_pRoomManager->GetRoom(RoomManager::RoomLookup::bigRoom2)->Draw();
	m_pTearManager->DrawBackTears();
	testSpider->Draw();
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
	m_pPlayer = new Isaac(m_TextureManager, isaacHealthBar, Point2f{ m_Window.width / 2.0f, m_Window.height / 2.0f });
}

void Game::DrawPlayer() const
{
	m_pPlayer->Draw();
}

void Game::UpdatePlayer(float elapsedSec)
{
	m_pPlayer->Update(elapsedSec, m_pTearManager, m_TextureManager, m_pRoomManager->GetRoom(RoomManager::RoomLookup::bigRoom2));
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
	m_pTearManager->UpdateTears(elapsedSec, m_pRoomManager->GetRoom(RoomManager::RoomLookup::bigRoom2)->GetGameObjects());
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
