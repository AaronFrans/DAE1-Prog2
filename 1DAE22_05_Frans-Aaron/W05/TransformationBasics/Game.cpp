#include "pch.h"
#include "Game.h"
#include "utils.h"


Game::Game(const Window& window)
	: m_Window{ window }
	, m_Vertices{}
	, m_Angle{ 0 }
	, m_ScaleFactor{ 1 }
	, m_Translate(0, 0)
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_Vertices.push_back(Point2f{ 48, 0 });
	m_Vertices.push_back(Point2f{ 48 * 2, 48 });
	m_Vertices.push_back(Point2f{ 48, 48 * 2 });
	m_Vertices.push_back(Point2f{ 0 ,  48 });

	m_TransformedVertices = m_Vertices;
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_A])
		m_Angle -= 60 * elapsedSec;
	else if (pStates[SDL_SCANCODE_D])
		m_Angle += 60 * elapsedSec;
	if (pStates[SDL_SCANCODE_W])
		m_ScaleFactor *= 1 + 3 * elapsedSec;
	else if (pStates[SDL_SCANCODE_S])
		m_ScaleFactor /= 1 + 3 * elapsedSec;
	if (pStates[SDL_SCANCODE_UP])
		m_Translate.y += 120 * elapsedSec;
	else if (pStates[SDL_SCANCODE_DOWN])
		m_Translate.y -= 120 * elapsedSec;
	else if (pStates[SDL_SCANCODE_LEFT])
		m_Translate.x -= 120 * elapsedSec;
	else if (pStates[SDL_SCANCODE_RIGHT])
		m_Translate.x += 120 * elapsedSec;

	Matrix2x3 trs{ Vector2f{m_ScaleFactor * cos(m_Angle), sin(m_Angle)},
		Vector2f{-sin(m_Angle), m_ScaleFactor * cos(m_Angle)},
		m_Translate };
	m_TransformedVertices = trs.Transform(m_TransformedVertices);

	m_ScaleFactor = 1;
	m_Translate = Vector2f{ 0,0 };
	m_Angle = 0;
}

void Game::Draw() const
{
	ClearBackground();

	utils::SetColor(Color4f{ 0,0,1,1 });
	utils::DrawPolygon(m_Vertices, true, 2);
	utils::DrawPolygon(m_TransformedVertices, true, 2);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
