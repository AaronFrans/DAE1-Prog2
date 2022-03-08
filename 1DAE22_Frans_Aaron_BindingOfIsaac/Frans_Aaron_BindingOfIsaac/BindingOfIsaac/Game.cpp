#include "pch.h"
#include "Game.h"
#include "Isaac.h"

Game::Game(const Window& window)
	: m_Window{ window }
	, m_TextureManager{}
{
	;
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	InitPlayer();
	InitTearManager();
}

void Game::Cleanup()
{
	DeleteTearManager();
	DeletePlayer();
}

void Game::Update(float elapsedSec)
{
	UpdateTearManager(elapsedSec);
	UpdatePlayer(elapsedSec);

}

void Game::Draw() const
{
	ClearBackground();
	DrawTearManager();
	DrawPlayer();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
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

void Game::InitPlayer()
{
	m_pPlayer = new Isaac(m_TextureManager, Point2f{ m_Window.width / 2.0f, m_Window.height / 2.0f });
}

void Game::DrawPlayer() const
{
	m_pPlayer->Draw();
}

void Game::UpdatePlayer(float elapsedSec)
{
	m_pPlayer->Update(elapsedSec, m_pTearManager);
}

void Game::DeletePlayer()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void Game::InitTearManager()
{
	m_pTearManager = new TearManager{ m_TextureManager.GetTexture(TextureManager::TextureLookup::Tears) };
}

void Game::DrawTearManager() const
{
	m_pTearManager->DrawTears();
}

void Game::UpdateTearManager(float elapsedSec)
{
	m_pTearManager->UpdateTears(elapsedSec);
}

void Game::DeleteTearManager()
{
	delete m_pTearManager;
	m_pTearManager = nullptr;
}
