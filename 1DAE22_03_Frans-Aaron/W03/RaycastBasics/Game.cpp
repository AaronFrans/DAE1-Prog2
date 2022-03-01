#include "pch.h"
#include "Game.h"
#include "utils.h"

Game::Game(const Window& window)
	: m_Window{ window }
	, m_RayP1{ m_Window.width / 2.0f, m_Window.height / 2.0f }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	InitSurface();
}

void Game::Cleanup()
{
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
}

void Game::Draw() const
{
	ClearBackground();
	DrawSurface();
	DrawRaycast();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_RayP2.x = (float)e.x;
	m_RayP2.y = (float)e.y;
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

void Game::InitSurface()
{
	m_Surface.push_back(Point2f{ 50, 50 });
	m_Surface.push_back(Point2f{ 450, 25 });
	m_Surface.push_back(Point2f{ 725, 50 });
	m_Surface.push_back(Point2f{ 725, 450 });
	m_Surface.push_back(Point2f{ 450, 475 });
	m_Surface.push_back(Point2f{ 50, 450 });
}

void Game::DrawSurface() const
{
	utils::SetColor(Color4f{ 1, 0.5f, 0, 1 });
	for (size_t i = 1; i <= m_Surface.size(); i++)
	{
		if (i == m_Surface.size())
			utils::DrawLine(m_Surface[0], m_Surface[i - 1], 4);
		else
			utils::DrawLine(m_Surface[i - 1], m_Surface[i], 4);
	}

}

void Game::DrawRaycast() const
{
	utils::SetColor(Color4f{ 1, 1, 0, 1 });
	utils::DrawLine(m_RayP1, m_RayP2, 4);

	utils::HitInfo hitInfo;

	if (utils::Raycast(m_Surface, m_RayP1, m_RayP2, hitInfo))
	{

		utils::SetColor(Color4f{ 1, 1, 0 ,1 });
		utils::DrawEllipse(hitInfo.intersectPoint, 4, 4);


		utils::SetColor(Color4f{ 0, 1, 0 ,1 });
		DrawVector(hitInfo.normal * 30, hitInfo.intersectPoint);



		utils::SetColor(Color4f{ 1, 1, 1 ,1 });
		Vector2f ray{ m_RayP1, m_RayP2 };
		Vector2f reflection{ ray.Reflect(hitInfo.normal) };
		DrawVector(reflection * (1 - hitInfo.lambda), hitInfo.intersectPoint);

	}



}



void Game::DrawVector(const Vector2f& v, const Point2f& p) const
{
	Point2f endPoint{ p + v };

	utils::DrawLine(p, endPoint);


}