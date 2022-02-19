#include "pch.h"
#include "Game.h"
#include "Vector2f.h"
#include "Ball.h"
#include "Texture.h"

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
	for (int i = 0; i < m_NrBalls; i++)
	{
		m_pBalls[i] = new Ball{ 
			Point2f{ float(rand() % 300 + 20), 100.0f},
			Vector2f{80.0f, 80.0f},
			Color4f{1, 1, 0, 1}, 
			float(rand() % 50 + 25)
		};
	}

	for (int i = 0; i < m_NrTextures; i++)
	{ 
		m_pTextures[i] = new Texture{ "../Resources/Images/DAE.png" };
	}
	
}

void Game::Cleanup( )
{
	for (int i = 0; i < m_NrBalls; i++)
	{
		delete m_pBalls[i];
		m_pBalls[i] = nullptr;
	}

	for (int i = 0; i < m_NrTextures; i++)
	{
		delete m_pTextures[i];
		m_pTextures[i] = nullptr;
	}
	

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

	for (int i = 0; i < m_NrBalls ; i++)
	{
		m_pBalls[i]->Update(
			elapsedSec, 
			Rectf{ 0, 0, m_Window.width, m_Window.height
			});
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	for (int i = 0; i < m_NrBalls; i++)
	{
		m_pBalls[i]->Draw();
	}

	for (int i = 0; i < m_NrTextures; i++)
	{
		m_pTextures[i]->Draw(
			Point2f{ 50, 0 + 70.0f * i },
			Rectf{
				0,
				0,
				m_pTextures[i]->GetWidth(),
				m_pTextures[i]->GetHeight()
			}
		);
	}
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

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
