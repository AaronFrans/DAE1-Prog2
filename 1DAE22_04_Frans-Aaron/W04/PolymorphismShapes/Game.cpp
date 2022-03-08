#include "pch.h"
#include <iostream>
#include "Game.h"
#include "DaeEllipse.h"
#include "DaeRectangle.h"
#include "DaeCircle.h"
#include "DaeRectLabel.h"
#include "DaeShape.h"
#include "Vector2f.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_TransSpeed{ 100.0f }
	, m_pFont{nullptr}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	OpenLabelFont( );
	CreateShapes( );
}

void Game::Cleanup( )
{
	DeleteShapes( );
	CloseLabelFont( );
}

void Game::Update( float elapsedSec )
{
	MoveShapes( elapsedSec );
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawShapes( );
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::OpenLabelFont( )
{
	m_pFont = TTF_OpenFont( "./Resources/DIN-Light.otf", 16 );
	if ( m_pFont == nullptr )
	{
		std::cerr << "Game::OpenLabelFont, error when calling TTF_OpenFont: " << TTF_GetError( ) << std::endl;
	}
}

void Game::CreateShapes( )
{
	m_pShapes.push_back( new DaeEllipse( Point2f{ 50.0f, 50.0f }, 30.0f, 40.0f, Color4f{ 1.0f, 0.6f, 0.07f, 1.0f }, true ) );
	m_pShapes.push_back( new DaeEllipse( Point2f{ 50.0f, 125.0f }, 60.0f, 70.0f, Color4f{ 1.0f, 0.89f, 0.71f, 1.0f }, true ) );
	m_pShapes.push_back( new DaeEllipse( Point2f{ 50.0f, 200.0f }, 50.0f, 70.0f, Color4f{ 1.0f, 0.89f, 0.71f, 1.0f }, false ) );

	m_pShapes.push_back( new DaeCircle( Point2f{ 125.0f, 50.0f }, 50.0f, Color4f{ 1.0f, 0.76f, 0.15f, 1.0f }, true ) );
	m_pShapes.push_back( new DaeCircle( Point2f{ 140.0f, 120.0f }, 80.0f, Color4f{ 0.85f, 0.65f, 0.8f, 1.0f}, true ) );

	m_pShapes.push_back( new DaeRectangle( Point2f{ 225.0f, 60.0f }, 50.0f, 80.0f, Color4f{ 1.0f, 0.27f, 0.0f, 1.00f } ) );
	m_pShapes.push_back( new DaeRectangle( Point2f{ 225.0f, 130.0f }, 50.0f, 40.0f, Color4f{ 1.0f, 0.27f, 0.31f, 1.0f } ) );

	m_pShapes.push_back( new DaeRectLabel( Point2f{ 350.0f, 35.0f }, 100.0f, 30.0f, Color4f{ 0.78f, 0.78f,0.78f, 1.0f },  "DAE", Color4f{ 0.0f, 0.0f, 0.0f, 1.0f },m_pFont ));
	m_pShapes.push_back( new DaeRectLabel( Point2f{ 350.0f, 105.0f }, 100.0f, 40.0f, Color4f{ 0.78f, 0.78f,0.78f, 1.0f }, "HOWEST", Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }, m_pFont ) );
}

void Game::CloseLabelFont( )
{
	if ( m_pFont != nullptr )
	{
		TTF_CloseFont( m_pFont );
		m_pFont = nullptr;
	}
}

void Game::DeleteShapes( )
{
	for (DaeShape* pShape : m_pShapes)
	{
		delete pShape;
	}
	m_pShapes.clear();
}

void Game::DrawShapes( ) const
{
	for (DaeShape* pShape : m_pShapes)
	{
		pShape->Draw();
	}
}

void Game::MoveShapes( float elapsedSec )
{
	Vector2f transVec{};

	// Check keyboard state for translation requests
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_RIGHT ] )
	{
		transVec.x += m_TransSpeed * elapsedSec;
	}
	if ( pStates[SDL_SCANCODE_LEFT] )
	{
		transVec.x -= m_TransSpeed * elapsedSec;
	}
	if ( pStates[SDL_SCANCODE_DOWN] )
	{
		transVec.y -= m_TransSpeed * elapsedSec;
	}
	if ( pStates[SDL_SCANCODE_UP] )
	{
		transVec.y += m_TransSpeed * elapsedSec;
	}

	// Translate shapes
	for (DaeShape* pShape : m_pShapes)
	{
		pShape->Translate(transVec);
	}
}

