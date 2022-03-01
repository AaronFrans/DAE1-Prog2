#include "pch.h"
#include "Game.h"
#include "utils.h"

Game::Game(const Window& window)
	: m_Window{ window }
	, m_MousePos()
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{

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

	//Surface
	Point2f SurfaceP1{ 350.0f, 50.0f };
	Point2f SurfaceP2{ 150.0f, 250.0f };
	utils::SetColor(Color4f{ 1, 0.5f, 0.2f ,1 });
	utils::DrawLine(SurfaceP1, SurfaceP2, 4);

	//The Ray
	Point2f rayP1{ 100.0f, 40.0f };
	Point2f rayP2{ 380.0f, 180.0f };
	utils::SetColor(Color4f{ 1, 1, 0 ,1 });
	utils::DrawLine(rayP1, m_MousePos, 2);

	//Raycast
	utils::HitInfo info{};
	std::vector<Point2f> surface{ SurfaceP1, SurfaceP2 };

	if (utils::Raycast(surface, rayP1, m_MousePos, info))
	{

		utils::SetColor(Color4f{ 1, 1, 0 ,1 });
		utils::DrawEllipse(info.intersectPoint, 4, 4);
		utils::DrawEllipse(info.intersectPoint, 4, 4);

		//Normal

		utils::SetColor(Color4f{ 0, 1, 0 ,1 });
		DrawVector(info.normal * 100, info.intersectPoint);

		//ReflectVector
		utils::SetColor(Color4f{ 1, 1, 1 ,1 });
		Vector2f ray{ rayP1, m_MousePos };
		Vector2f reflection{ ray.Reflect(info.normal) };
		DrawVector(reflection * (1 - info.lambda), info.intersectPoint);


	}
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
	m_MousePos.x = (float)e.x;
	m_MousePos.y = (float)e.y;

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

void Game::DrawVector(const Vector2f& v, const Point2f& p) const
{
	Point2f endPoint{ p + v };

	utils::DrawLine(p, endPoint);


}
