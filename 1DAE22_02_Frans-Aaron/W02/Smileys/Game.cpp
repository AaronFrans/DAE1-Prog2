#include "pch.h"
#include "Game.h"
#include "Smiley.h"
#include "utils.h"

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
	InitSmileys();
}

void Game::Cleanup()
{
	DeleteSmileys();
}

void Game::Update(float elapsedSec)
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
	UpdateSmileys(elapsedSec);
	CheckHighestSmiley();
}

void Game::Draw() const
{
	ClearBackground();
	utils::DrawRect(m_SafeRect);
	DrawSmileys();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		SpeedupSmileys();
		break;
	case SDLK_DOWN:
		SlowdownSmileys();
		break;
	case SDLK_DELETE:
		DeleteSleepingSmileys();
		break;
	}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		CheckClickOnSmiley(Point2f{ (float)e.x, (float)e.y });
		break;
	case SDL_BUTTON_RIGHT:
		std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		std::cout << " middle button " << std::endl;
		break;
	}
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

void Game::InitSmileys()
{
	for (int i = 0; i < m_NrSmileys; i++)
	{
		m_pSmileys[i] = new Smiley(Point2f(i * 50.0f, m_Window.height / 2.0f));
	}
}

void Game::DeleteSmileys()
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley != nullptr)
		{
			delete smiley;
			smiley = nullptr;
		}
	}
}

void Game::DrawSmileys() const
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley != nullptr)
			smiley->Draw();

	}
}

void Game::UpdateSmileys(float elapsedSec)
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley != nullptr)
			smiley->Update(elapsedSec, Rectf{ 0, 0, m_Window.width, m_Window.height }, m_SafeRect);

	}
}

void Game::CheckClickOnSmiley(Point2f mousePos)
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley != nullptr)
			smiley->HitTest(mousePos);
	}
}

void Game::CheckHighestSmiley()
{
	float highest = -100;
	int index = -1;
	for (int i = 0; i < m_NrSmileys; i++)
	{
		if (m_pSmileys[i]->GetPosition().y > highest && !m_pSmileys[i]->IsSleeping() && m_pSmileys[i] != nullptr)
		{
			index = i;
			highest = m_pSmileys[i]->GetPosition().y;

		}
	}

	for (int i = 0; i < m_NrSmileys; i++)
	{
		if (i == index)
			m_pSmileys[i]->SetHighest(true);
		else
		{
			if (m_pSmileys[i] != nullptr)
				m_pSmileys[i]->SetHighest(false);
		}
	}
}

void Game::SpeedupSmileys()
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley != nullptr)
			smiley->IncreaseSpeed();
	}
}

void Game::SlowdownSmileys()
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley != nullptr)
			smiley->DecreaseSpeed();
	}
}

void Game::DeleteSleepingSmileys()
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley != nullptr && smiley->IsSleeping())
		{
			delete smiley;
			smiley = nullptr;
		}
	}
}
