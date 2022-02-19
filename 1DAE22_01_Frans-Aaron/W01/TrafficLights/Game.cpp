#include "pch.h"
#include "Game.h"
#include "TrafficLight.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	InnitLights();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
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

	UpdateLights(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );

	DrawLights();

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
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

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
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

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		for (TrafficLight* light : m_Lights)
		{
			light->DoHitTest(Point2f{
				float(e.x),
				float(e.y)
				});
		}

		break;
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InnitLights()
{

	for (int i = 0; i < m_Colls; i++)
	{
		for (int j = 0; j < m_Rows; j++)
		{
			if (i == 0 && j == 0)
			{

				m_Lights.push_back(new TrafficLight(
					Point2f{ 0,0 }
				));

			}
			else
			{
				m_Lights.push_back(new TrafficLight(
					Point2f{ (m_Lights[0]->GetWidth() + 2) * j, (m_Lights[0]->GetHeight() + 2) * i }
				));
			}
		}
	}

}

void Game::DrawLights() const
{
	for (TrafficLight* light : m_Lights)
	{
		light->Draw();
	}
}

void Game::UpdateLights(float elapsedSec)
{
	for (TrafficLight* light : m_Lights)
	{
		light->Update(elapsedSec);
	}
}
