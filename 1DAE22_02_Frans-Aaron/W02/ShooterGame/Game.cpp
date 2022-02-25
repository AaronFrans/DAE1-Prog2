#include "pch.h"
#include "Game.h"
#include "Enemy.h"
#include "utils.h"
#include "Avatar.h"
#include <iostream>


Game::Game(const Window& window)
	:m_Window{ window }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	InitGameParams();
	InitEnemies();
	InitPlayer();
}

void Game::Cleanup()
{
	DeleteEnemies();
	DeletePlayer();
}

void Game::Update(float elapsedSec)
{
	UpdatePlayer(elapsedSec);
}

void Game::Draw() const
{
	ClearBackground();
	DrawEnemies();
	//utils::SetColor(Color4f{ 1, 1, 1, 1 });
	//utils::FillRect(m_PlayerBoundary);
	DrawPlayer();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	m_pPlayer->ProcessKeyDownEvent(e);
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
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

void Game::InitGameParams()
{

	float EnemyRectWidth = m_EnemySize * m_NrOfColumns + (m_EnemyBorder * (m_NrOfColumns + 1));
	float EnemyRectHeight = m_EnemySize * m_NrOfRows + (m_EnemyBorder * (m_NrOfRows + 1));
	float EnemyRectBottom = m_Window.height - m_EnemyRectBorder - EnemyRectHeight;
	float EnemyRectLeft = (m_Window.width / 2.0f) - m_EnemyBorder - EnemyRectWidth / 2.0f;

	m_EnemiesBoundary = Rectf{ EnemyRectLeft, EnemyRectBottom, EnemyRectWidth,  EnemyRectHeight };
	m_PlayerBoundary = Rectf{ EnemyRectLeft, 0, EnemyRectWidth, m_Window.height };

}

void Game::InitEnemies()
{
	for (int i = 1; i <= m_NrOfColumns; i++)
	{
		for (int j = 1; j <= m_NrOfRows; j++)
		{
			m_pEnemies.push_back(new Enemy{ Point2f{
			m_EnemiesBoundary.left + m_EnemyBorder + (m_EnemySize * (i - 1)) + (m_EnemyBorder * (i - 1)) + (m_EnemySize / 2.0f),
			m_EnemiesBoundary.bottom + m_EnemyBorder + (m_EnemySize * (j - 1)) + (m_EnemyBorder * (j - 1)) + m_EnemySize / 2},
			m_EnemySize,
			m_EnemySize });
		}

	}
}

void Game::DeleteEnemies()
{
	for (int i = 0; i < m_pEnemies.size(); i++)
	{
		delete m_pEnemies[i];
		m_pEnemies[i] = nullptr;
	}

}

void Game::DrawEnemies() const
{
	for (Enemy* enemy : m_pEnemies)
	{
		enemy->Draw();
		
	}
}

void Game::InitPlayer()
{
	m_pPlayer = new Avatar(Point2f{ m_Window.width / 2.0f, 60 }, 25, 30);
	m_pPlayer->SetBoundaries(m_PlayerBoundary);
}

void Game::DeletePlayer()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void Game::DrawPlayer() const
{
	m_pPlayer->Draw();
}

void Game::UpdatePlayer(float elapsedSec)
{
	m_pPlayer->Update(elapsedSec, m_pEnemies[0], m_MaxNrEnemies);
}
